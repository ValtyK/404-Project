#include <stdio.h>
#include "musique.h"

int main(int argc, char **argv) {

    int sample_rate = SAMPLE_RATE;      // 44100 Hz
    int num_channels = 2;               // 1 = mono, 2 = stéréo
    int bits_per_sample = 16;           // 16-bit PCM
    double duration = 7.0;              // durée du fichier WAV en secondes

    FILE *file = fopen(argv[1], "wb");

    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir %s", argv[1]);
        return 1;
    }

    init_audio_buffers(sample_rate, num_channels, duration);
    write_wav_header(file, sample_rate, num_channels, bits_per_sample, duration);

    // Exemple : un accord autour de LA3 (220 Hz), de 1s à 3s
    generate_signal_perso(0, 3.0, 220.0, 3000.0, sample_rate);  // LA3
    generate_signal_perso(1.0, 3.0, 220.0 * pow(2.0, 7.0 / 12.0), 3000.0, sample_rate);  // MI
    generate_signal_perso(3.0, 5.0, 330.0 * pow(2.0, 7.0 / 12.0), 3000.0, sample_rate);  // MI
    generate_signal_perso(5.0, 7.0, 110.0 * pow(2.0, 7.0 / 12.0), 3000.0, sample_rate);  // MI
    
    // ici je génère plusieurs accords en synthèse additive qui se superposent dans le .wav
    
    generate_envelope(0, 7, 30.0, 20.0, 80.0, 30.0, sample_rate);

    write_normalized_audio(file, bits_per_sample);

    fclose(file);
    free_audio_buffers();

    printf("> Fichier '%s' généré avec succès.\n", argv[1]);
    return 0;
}
