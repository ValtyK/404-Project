#include <stdio.h>
#include <stdlib.h>

#include "arbre/type_ast.h"
#include "syntaxe/analyse_syntaxique.h"
#include "arbre/ast_parcours.h"
#include "../lib/musique.h"

int main (int argc, char* argv[]) {
    int syntaxe_correcte ; 
    Ast A;
    switch (argc) {
        case 1:
            syntaxe_correcte = analyser("", &A);
            break;
        case 2:
            syntaxe_correcte = analyser(argv[1], &A);
            break;
        default:
            printf("Erreur : nombre d'arguments incorrects !\n");
            exit(1);
    }
    if (syntaxe_correcte) {
        printf("Test_syntaxe : OK\n");
        printf("Nombre de mesures: %d\n", calcul_nb_mesures(A));
        int nbm = calcul_nb_mesures(A);
        FILE* f = fopen("musique.wav","wb");
        init_audio_buffers(SAMPLE_RATE, NUM_CHANNELS, duree_totale(BPM, 4, nbm));
        write_wav_header(f, SAMPLE_RATE, NUM_CHANNELS, BITS_PER_SAMPLE, duree_totale(BPM, 4, nbm));


        double t = 0.0;
        parcours(A, &t);

        write_normalized_audio(f, BITS_PER_SAMPLE);
        free_audio_buffers();
        fclose(f);
    }
}