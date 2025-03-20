#ifndef MUSIQUE_H
#define MUSIQUE_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Constante PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Def de la frequence d'echantillonage (nb d'echantillons par seconde)
#define SAMPLE_RATE 44100 // standard CD

// Definition du volume (entre 0 et 32 pourdu son 16-bit)
#define VOLUME 3000

// Frequence reference du LA4 (changable)
#define REF_FREQUENCY 440.0

typedef struct Note {
    char name[5];       // Nom de la note (DO, RE#, etc.)
    double duration;    // Durée en secondes
} Note;

// Fonction pour le .wav
void write_wav_header(FILE *file, int sample_count);
void play_sine_wave(FILE *file, double frequency, double duration);

// Conversion note en freq.
double note_to_frequency(const char *note);

#endif
