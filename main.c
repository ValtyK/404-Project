#include <stdio.h>
#include "musique.h"

int main(int argc, char **argv) {

    int sample_rate = SAMPLE_RATE;          // 44100 Hz
    int num_channels = NUM_CHANNELS;        // 1 = mono, 2 = stéréo
    int bits_per_sample = BITS_PER_SAMPLE;  // 16-bit PCM
    
    double duration = 11; // durée du fichier WAV en secondes

    FILE *file = fopen(argv[1], "wb");

    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir %s", argv[1]);
        return 1;
    }

    init_audio_buffers(sample_rate, num_channels, duration);
    write_wav_header(file, sample_rate, num_channels, bits_per_sample, duration);

    // Exemple : un accord autour de LA3 (220 Hz), de 1s à 3s
    // ici je génère plusieurs accords en synthèse additive qui se superposent dans le .wav
    // generate_signal_perso(0.0, 3.0, 220.0, 3000.0, sample_rate);  // LA3
    // generate_signal_perso(1.0, 3.0, 220.0 * pow(2.0, 7.0 / 12.0), 3000.0, sample_rate);  // MI
    // generate_signal_perso(3.0, 5.0, 330.0 * pow(2.0, 7.0 / 12.0), 3000.0, sample_rate);  // MI
    // generate_signal_perso(5.0, 7.0, 110.0 * pow(2.0, 7.0 / 12.0), 3000.0, sample_rate);  // MI
    
    // Hop là faire des accords sympa
    // double freqs[] = {261.626, 329.628, 391.995}; // Do, Mi, Sol
    // generate_chord(7.0, 9.0, freqs, 3, 3000.0, sample_rate);
    
    // Utilisation de note_to_frequency
    // double note1 = note_to_frequency("C", 4);
    // double note2 = note_to_frequency("E", 4);
    // double note3 = note_to_frequency("G", 4);
    // printf("note1 = %.3f Hz\nnote2 = %.3f Hz\nnote3 = %.3f Hz\n", note1, note2, note3);
    // double freqs_2[] = {note1, note2, note3}; // Do, Mi, Sol
    // generate_chord(9.0, 11.0, freqs_2, 3, 3000.0, sample_rate);
    
    // generate_envelope(0.0, 11.0, 30.0, 20.0, 80.0, 30.0, sample_rate);

    double ma_freq = note_to_frequency("C", 4);
    generate_signal(0, 2, ma_freq, 3000.0, sample_rate);
    generate_signal(2, 4, ma_freq, 3000.0, sample_rate);
    generate_signal(4, 11, ma_freq, 3000.0, sample_rate);
    
    generate_signal(6, 11, 440, 1000, sample_rate);
    generate_signal(6, 11, 330, 1000, sample_rate);
    generate_signal(6, 11, 220, 1000, sample_rate);

    write_normalized_audio(file, bits_per_sample);

    fclose(file);
    free_audio_buffers();

    printf("> File '%s' successfully generated.\n", argv[1]);
    return 0;
}
