#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_symboles.h"
int main() {
    Ast *A = malloc(sizeof(Ast));
    Ast *Adr = malloc(sizeof(Ast));
    Ast *Anote = malloc(sizeof(Ast));
    int val;
    double w;

    // Initialisation des noeuds
    A->nature = Noeud_SEQDR;
    A->gauche = Adr;
    A->droite = Anote;
    A->suite = NULL;

    Adr->nature = Noeud_DR;
    Adr->valeur = 4;

    Anote->nature = Noeud_NOTE;
    Anote->string = "C";
    Anote->valeur = 4;

    insererMeloTS("x", A);
    afficheTS();

    free(A);
    free(Adr);
    free(Anote);

    return 0;
}
