#include "musique.h"

int main() {

    FILE *file = fopen("musique.wav", "wb");
    
    if (!file) {
        perror("Erreur : impossible d'ouvrir musique.wav");
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
        {"DO5", 0.3}, // 1
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

    size_t melody_size = sizeof(melody_1) / sizeof(Note);
    
    for (size_t i = 0; i < melody_size; i++) {

        double frequency = note_to_frequency(melody_1[i].name);

        printf("[%s] -> Frequence : %.2f Hz\n", melody_1[i].name, frequency);

        play_sine_wave(file, frequency, melody_1[i].duration);

    }

    fclose(file);
    
    printf("> Fichier 'musique.wav' généré.\n");
    return 0;
}
