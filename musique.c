#include "musique.h"

#include <math.h>
#include <stdlib.h>

// Fonction pour calculer la fréquence d'une note donnée sous forme "DO4", "RE#3", etc.
double note_to_frequency(const char *note) {

    const char *notes[] = {"DO", "DO#", "RE", "RE#", "MI", "FA", "FA#", "SOL", "SOL#", "LA", "LA#", "SI"};

    int semitone_offset = 0;
    int octave = 0;
    char note_name[6] = ""; // taille max : "SOL#4\0"

    // Extraire le nom de la note et l’octave depuis la chaîne (ex: "FA#3")
    if (sscanf(note, "%5[^0123456789]%d", note_name, &octave) != 2) {
        return 0;  // Erreur si le format est invalide
    }

    // Trouver l'index de la note dans le tableau
    for (int i = 0; i < 12; i++) {
        if (strcmp(note_name, notes[i]) == 0) {
            semitone_offset = i - 9; // Décalage par rapport à LA (LA est l’index 9)
            break;
        }
    }

    // Calculer l'écart en demi-tons par rapport à LA4
    int total_semitones = semitone_offset + (octave - 4) * 12;

    // Appliquer la formule : f = 440 * 2^(n/12)
    return REF_FREQUENCY * pow(2.0, total_semitones / 12.0);
}

/**
 * @brief Ecrit l'en-tête d'un fichier WAV
 * 
 * @param file Pointeur vers le fichier ouvert en écriture
 * @param sample_count Nombre total d'échantillons audio à écrire
 * 
 */
void write_wav_header(FILE *file, int sample_count) {

    // Parametres WAV (format PCM 16-bit)
    int32_t sample_rate = SAMPLE_RATE;
    int32_t chunk_size = 36 + sample_count * sizeof(int16_t);
    int32_t subchunk1_size = 16;
    int32_t subchunk2_size = sample_count * sizeof(int16_t);
    int16_t audio_format = 1;  // PCM pas compressé
    int16_t num_channels = 1;  // Mono
    int32_t byte_rate = SAMPLE_RATE * sizeof(int16_t);
    int16_t block_align = sizeof(int16_t);
    int16_t bits_per_sample = 16;

    fwrite("RIFF", 1, 4, file);         // Chunck ID "RIFF"
    fwrite(&chunk_size, 4, 1, file);    // Taille totale du fichier
    fwrite("WAVE", 1, 4, file);         // Format WAV

    fwrite("fmt ", 1, 4, file);             // Sous-chunk "fmt "
    fwrite(&subchunk1_size, 4, 1, file);    // Taille du sous-chunk

    fwrite(&audio_format, 2, 1, file);      // Format PCM
    fwrite(&num_channels, 2, 1, file);      // Nombre de canaux (1 = mono)
    fwrite(&sample_rate, 4, 1, file);       // Freq. echantillonage
    fwrite(&byte_rate, 4, 1, file);         // Byte rate (nb octets par seconde)
    fwrite(&block_align, 2, 1, file);       // Alignement des blocs
    fwrite(&bits_per_sample, 2, 1, file);   // Bits par echantillon (16-bit)
    fwrite("data", 1, 4, file);             // Chunk ID "data"
    fwrite(&subchunk2_size, 4, 1, file);    // Taille des données audio
}

// Génère et écrit une onde sin.
void play_sine_wave_old(FILE *file, double frequency, double duration) {
    int sample_count = SAMPLE_RATE * duration;
    int16_t sample;

    for (int i = 0; i < sample_count; i++) {
        sample = VOLUME * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE);
        fwrite(&sample, sizeof(int16_t), 1, file);
    }
}

// Nouvelle version sans coupures :

/**
 * @brief Génère une onde sinusoïdale correspondant à une note et l'écrit dans un fichier WAV
 * 
 * @param file Pointeur vers le fichier WAV ouvert en écriture
 * @param frequency Fréquence de la note (en Hz)
 * @param duration Durée de la note (en secondes)
 */
void play_sine_wave(FILE *file, double frequency, double duration) {

    int sample_count = SAMPLE_RATE * duration; // Nb total d'echantillons
    int16_t sample; // Stocke chaque echantillon (16-bit signé)
    
    for (int i = 0; i < sample_count; i++) {
        double envelope = 1.0;

        // Ajout d'une courbe d'attaque et de relâchement pour eviter les "click"
        double fade_time = 0.02;  // 20 ms de fade-in et fade-out
        int fade_samples = SAMPLE_RATE * fade_time;

        if (i < fade_samples) {
            envelope = (double)i / fade_samples;  // Fade-in
        } else if (i > sample_count - fade_samples) {
            envelope = (double)(sample_count - i) / fade_samples;  // Fade-out
        }

        // Generation de l'onde + enveloppe
        sample = VOLUME * envelope * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE);

        // Ecriture de l'echantillon dans le fichier
        fwrite(&sample, sizeof(int16_t), 1, file);
    }
}

