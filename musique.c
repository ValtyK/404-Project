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

