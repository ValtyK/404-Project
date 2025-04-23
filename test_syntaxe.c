#include <stdio.h>
#include <stdlib.h>

#include "type_ast.h"
#include "syntaxe/analyse_syntaxique.h"
#include "arbre/ast_parcours.h"

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
    }
}