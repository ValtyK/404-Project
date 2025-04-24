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

#define REF_FREQUENCY 440.0 // Frequence reference du LA4 (changable)

#define BPM 120.0

#define SIGNATURE_NUMERATEUR 4
#define SIGNATURE_DENOMINATEUR 4

// Nombre max de notes dans un accord
#define MAX_NOTES_IN_CHORD 8

// Buffers audio globaux
extern double *left_buffer;
extern double *right_buffer;
extern unsigned long total_samples;

// Fonctions d'ecriture dans le .wav
void write_little_endian(unsigned int octets, int taille, FILE *fichier);
void write_wav_header(FILE *file, int sample_rate, int num_channels, int bits_per_sample, double duration_sec);
void write_normalized_audio(FILE *file, int bits_per_sample);

// Gestion de base des buffers audio
void init_audio_buffers(int sample_rate, int num_channels, double duration_sec);
void free_audio_buffers(void);

// Ecriture dans les buffers audio gout caca
void generate_signal_perso(double t1, double t2, double freq, double amp, int sample_rate); // fonction en bordel qui m'a permi de comprendre des choses
void generate_signal(double t1, double t2, double freq, double amp, int sample_rate); // pour générer un signal simple (1 frequence)
void generate_chord(double t1, double t2, const double *frequencies, int count, double amp, int sample_rate); // pour générer des accords
void generate_envelope(double t1, double t2, double attack, double decay, double sustain, double release, int sample_rate); // generer de l'enveloppe

// Fonctions diverses (déplacer dans une autre fichier à l'avenir)
double note_to_frequency(const char *note_name, int octave);
double duree_totale(double bpm, int numerateur, int nb_mesures);

#endif
