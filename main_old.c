#include "musique.h"
#include <stdio.h>

int main(int argc, char ** argv) {

    FILE *file = fopen(argv[1], "wb");
    
    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir %s", argv[1]);
        return 1;
    }

    // Placeholder pour l'en-tête WAV
    write_wav_header(file, SAMPLE_RATE * 30);  // 10 secondes max

    // Melodie : Do Do Do Re Mi Re Do Mi Re Re Do
    // Note melody_1[] = {
    //     {261.63, 0.3}, {261.63, 0.3}, {261.63, 0.3},
    //     {293.66, 0.3}, {329.63, 0.6}, {293.66, 0.6},
    //     {261.63, 0.3}, {329.63, 0.3}, {293.66, 0.3},
    //     {293.66, 0.3}, {261.63, 0.6}
    // };

    Note melody_1[] = {
        {"DO5", 0.3}, {"DO5", 0.3}, {"DO5", 0.3},
        {"RE5", 0.3}, {"MI5", 0.6}, {"RE5", 0.6},
        {"DO5", 0.3}, {"MI5", 0.3}, {"RE5", 0.3},
        {"RE5", 0.3}, {"DO5", 1.2},
        {"DO5", 0.3}, {"DO5", 0.3}, {"DO5", 0.3},
        {"RE5", 0.3}, {"MI5", 0.6}, {"RE5", 0.6},
        {"DO5", 0.3}, {"MI5", 0.3}, {"RE5", 0.3},
        {"RE5", 0.3}, {"DO5", 1.2},
        {"RE5", 0.3}, {"RE5", 0.3}, {"RE5", 0.3},
        {"RE5", 0.3}, {"LA4", 0.6}, {"LA4", 0.6},
        {"RE5", 0.3}, {"DO5", 0.3}, {"SI4", 0.3},
        {"LA4", 0.3}, {"SOL4", 1.2},
        {"DO5", 0.3}, {"DO5", 0.3}, {"DO5", 0.3},
        {"RE5", 0.3}, {"MI5", 0.6}, {"RE5", 0.6},
        {"DO5", 0.3}, {"MI5", 0.3}, {"RE5", 0.3},
        {"RE5", 0.3}, {"DO5", 1.2}
    };

    Note melody_2[] = {
        {"DO5-DO4-DO6", 0.3}, // 1
        {"DO#5", 0.15}, // binaire (1/2)
        {"RE5", 0.15},
        {"RE#5", 0.3},
        {"MI5", 0.1}, // ternaire (1/3)
        {"FA5", 0.1},
        {"FA#5", 0.1},
        {"SOL5", 0.3},
        {"SOL#5", 0.3},
        {"LA5", 0.3},
        {"LA#5", 0.2}, // ternaire (2/3)
        {"SI5", 0.2},
        {"DO6", 0.2}
    };

    float regu_temp = 0.5;
    Note melody_3[] = {
        {"DO5", regu_temp},
        {"DO#5", regu_temp},
        {"RE5", regu_temp},
        {"RE#5", regu_temp},
        {"MI5", regu_temp},
        {"FA5", regu_temp},
        {"FA#5", regu_temp},
        {"SOL5", regu_temp},
        {"SOL#5", regu_temp},
        {"LA5", regu_temp},
        {"LA#5", regu_temp},
        {"SI5", regu_temp},
        {"DO6", regu_temp}
    };

    size_t melody_size = sizeof(melody_2) / sizeof(Note);
    
    for (size_t i = 0; i < melody_size; i++) {

        double frequency = note_to_frequency(melody_2[i].name);

        printf("[%s] -> Frequence : %.2f Hz (%.2f)\n", melody_2[i].name, frequency, melody_2[i].duration);

        // play_sine_wave(file, frequency, melody_2[i].duration);
        play_chord(file, melody_2[i].name, melody_2[i].duration);

    }

    fclose(file);
    
    printf("> Fichier 'musique.wav' généré.\n");
    return 0;
}
