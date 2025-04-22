#include <stdio.h>
#include <stdlib.h>

#include "lexique/syntaxe_lexique.h"
#include "syntaxe/analyse_syntaxique.h"

int main (int argc, char* argv[]) {
    int syntaxe_correcte ; 

    switch (argc) {
        case 1:
            syntaxe_correcte = analyer("");
            break;
        case 2:
            syntaxe_correcte = analyser(argv[1]);
            break;
        default:
            printf("Erreur : nombre d'arguments incorrects !\n");
            exit(1);
    }
    if (syntaxe_correcte) {
        printf("Test_syntaxe : OK");
    }
}