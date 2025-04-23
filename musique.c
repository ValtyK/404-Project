#include "musique.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double *left_buffer = NULL;
double *right_buffer = NULL;
unsigned long total_samples = 0;

void write_little_endian(unsigned int octets, int taille, FILE *fichier) {
    unsigned char faible ;
    
    while(taille > 0) {   
        faible = octets & 0x000000FF ;
        fwrite(&faible, 1, 1, fichier) ;
        octets = octets >> 8 ;
        taille = taille - 1 ;
    }
}

void write_wav_header(FILE *file, int sample_rate, int num_channels, int bits_per_sample, double duration_sec) {

    // Calculs de con
    unsigned int byte_rate = sample_rate * num_channels * bits_per_sample / 8; // Debit en octet par seconde
    unsigned short block_align = num_channels * bits_per_sample / 8; // nb d'octets pour un echantillon complet
    unsigned int data_size = (int)(sample_rate * duration_sec) * block_align; // taille totale des donnees audio en octets
    unsigned int chunk_size = 36 + data_size; // taille du fichier moins 8 octets

    // Header RIFF
    fwrite("RIFF", 1, 4, file); // Chunck ID
    write_little_endian(chunk_size, 4, file); // Chunk Size
    fwrite("WAVE", 1, 4, file); // Format

    // FMT subchunk
    fwrite("fmt ", 1, 4, file); // Subchunk1 ID
    write_little_endian(16, 4, file); // Subchunk1 size (PCM)
    write_little_endian(1, 2, file); // Audio format (1 = PCM)
    write_little_endian(num_channels, 2, file); // Nombre de canaux (1 = mono, 2 = stereo)
    write_little_endian(sample_rate, 4, file); // Freq. echantillonage
    write_little_endian(byte_rate, 4, file);
    write_little_endian(block_align, 2, file);
    write_little_endian(bits_per_sample, 2, file); // bits par echantillon (16 bits par exemple)

    // DATA subchunk
    fwrite("data", 1, 4, file); // Subchunk2 ID
    write_little_endian(data_size, 4, file); // Subchunk2 size
}

void init_audio_buffers(int sample_rate, int num_channels, double duration_sec) {

    // Calcul nb total echantillons
    total_samples = (unsigned long)(sample_rate * duration_sec);

    if (num_channels == 1) {
        left_buffer = calloc(total_samples, sizeof(double));
        if (!left_buffer) {
            fprintf(stderr, "Error: failed to allocate mono buffer\n");
            free(left_buffer);
            exit(EXIT_FAILURE);
        }
        right_buffer = left_buffer; // meme buffer en mono
    } else if (num_channels == 2) {
        left_buffer = calloc(total_samples, sizeof(double));
        right_buffer = calloc(total_samples, sizeof(double));
        if (!left_buffer || !right_buffer) {
            fprintf(stderr, "Error: failed to allocate stereo buffers\n");
            free(left_buffer);
            free(right_buffer);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Error: unsupported channel count (%d).\n", num_channels);
        exit(EXIT_FAILURE);
    }
}

void free_audio_buffers(void) {
    if (left_buffer) {
        free(left_buffer);
    }
    if (right_buffer && (right_buffer != left_buffer)) {
        free(right_buffer);
    }

    left_buffer = NULL;
    right_buffer = NULL;
    total_samples = 0;
}

void generate_signal_perso(double t1, double t2, double freq, double amp, int sample_rate) {
    unsigned int i, j;
    double omega = 2.0 * M_PI * freq;
    double dt = 1.0 / sample_rate;
    double t = 0.0;

    unsigned int start = (unsigned int)(t1 * sample_rate);
    unsigned int end   = (unsigned int)(t2 * sample_rate);

    if (end > total_samples) end = total_samples;

    for (i = start; i < end; i++) {
        double sum = 0.0;

        for (j = 1; j <= 7; j++) {
            sum += amp / (pow(j, 2) * (1.0 + pow(t, j))) *
                (sin(j * omega * t)
                + sin(j * omega * pow(2.0, 3.0 / 12.0) * t)
                + sin(j * omega * pow(2.0, 7.0 / 12.0) * t));
        }

        left_buffer[i] += sum;
        right_buffer[i] += sum;

        t += dt;
    }
}

void generate_chord(double t1, double t2, const double *frequencies, int count, double amp, int sample_rate) {
    
    unsigned int i, j, k;
    // i: index echantillon buffer
    // j: index d'harmonique (1 à 7)
    // k: index des frequences dans l'accord
    double dt = 1.0 / sample_rate; // durée d'un echantillon
    double t = 0.0; // horloge locale en secondes (temps accumulé)

    // Indices d'echantillon correspondant a t1 et t2
    unsigned int start = (unsigned int)(t1 * sample_rate);
    unsigned int end = (unsigned int)(t2 * sample_rate);
    if (end > total_samples) end = total_samples;

    // parcours des echant. de t1 à t2
    for (i = start; i < end; i++) {

        // Somme des signaux a un instant t
        double sample = 0.0;

        // parcours de chaque frequence f de l'accord
        for (k = 0; k < count; k++) {

            double omega = 2.0 * M_PI * frequencies[k]; // pulsation angulaire
            
            // ajout des 7 premiers harmoniques pour chaque note (synth. additive)
            // on enrichit une onde en ajoutant les multiples entiers de sa fondamentale
            for (j = 1; j <= 7; j++) {
                sample += (amp / count) / (pow(j, 2)
                        * (1.0 + pow(t, j)))
                        * sin(j * omega * t);
                
                // (amp / count) : repartir l'amplitude entre les notes
                // 1 / pow(j, 2) : l'amplitude des harmoniques diminue prop à 1/j²
                // 1 / (1 + pow(t, j)) : transitions douces (ajout perso)
                // sin(j * omega * t) : sinusoide de frequence j*f (harmonique j)
            }
        }

        // Ajout du résultat dans les buffers stereo
        left_buffer[i] += sample;
        right_buffer[i] += sample;

        // On incrémente le temps courant
        t += dt;
    }
}


void write_normalized_audio(FILE *file, int bits_per_sample) {
    unsigned long i;
    double max_val = 1e-16;
    int max_amp = (1 << (bits_per_sample - 1)) - 1;

    for (i = 0; i < total_samples; i++) {
        if (fabs(left_buffer[i]) > max_val)  max_val = fabs(left_buffer[i]);
        if (fabs(right_buffer[i]) > max_val) max_val = fabs(right_buffer[i]);
    }

    for (i = 0; i < total_samples; i++) {
        int16_t s_l = (int16_t)((left_buffer[i]  / max_val) * max_amp);
        int16_t s_r = (int16_t)((right_buffer[i] / max_val) * max_amp);
        write_little_endian((unsigned short)s_l, 2, file);
        write_little_endian((unsigned short)s_r, 2, file);
    }
}

void generate_envelope(double t1, double t2, double attack, double decay, double sustain, double release, int sample_rate) {
    unsigned int i;

    unsigned int i1 = (unsigned int)(t1 * sample_rate);
    unsigned int i5 = (unsigned int)(t2 * sample_rate);
    if (i5 > total_samples) i5 = total_samples;

    unsigned int i2 = i1 + (unsigned int)((i5 - i1) * (attack / 100.0));
    unsigned int i3 = i1 + (unsigned int)((i5 - i1) * ((attack + decay) / 100.0));
    unsigned int i4 = i1 + (unsigned int)((i5 - i1) * (1.0 - release / 100.0));

    if (i2 > i5) i2 = i5;
    if (i3 > i5) i3 = i5;
    if (i4 > i5) i4 = i5;

    // Attack
    for (i = i1; i < i2; i++) {
        double env = (i - i1) / (double)(i2 - i1);
        left_buffer[i] *= env;
        right_buffer[i] *= env;
    }

    // Decay
    for (i = i2; i < i3; i++) {
        double env = (100.0 - ((i - i2) / (double)(i3 - i2)) * (100.0 - sustain)) / 100.0;
        left_buffer[i] *= env;
        right_buffer[i] *= env;
    }

    // Sustain
    for (i = i3; i < i4; i++) {
        double env = sustain / 100.0;
        left_buffer[i] *= env;
        right_buffer[i] *= env;
    }

    // Release
    for (i = i4; i < i5; i++) {
        double env = (sustain - ((i - i4) / (double)(i5 - i4)) * sustain) / 100.0;
        left_buffer[i] *= env;
        right_buffer[i] *= env;
    }
}

