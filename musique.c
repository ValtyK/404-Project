#include "musique.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

