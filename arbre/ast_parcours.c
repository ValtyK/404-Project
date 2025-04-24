#include <stdlib.h>
#include <stdio.h>

#include "../musique.h"
#include "ast_parcours.h"

/*
void aff_operateur(TypeOp op) {
	switch (op) {
		case N_AFF:
			printf(" = ") ;
			break;

	} 
}
*/
/*
void afficherA(Ast expr) {
	switch (expr->nature) {
        case Noeud_OPERATION:
            afficherA(expr->gauche);
            aff_operateur(expr->operateur) ;
            afficherA(expr->droite);
            break ;
        case Noeud_NOTE:
            printf(" %s", expr->string);
            afficherA(expr->gauche);
            if (expr->droit != NULL) {
                printf(",");
                afficherA(expr->droit);
            }
            break;
        case Noeud_DR:
            printf(" %s", expr->string);
            printf("(");
            afficherA(expr->gauche);
            printf(")");
            if (expr->droit != NULL) {
                afficherA(expr->droit);
            }
            break;
        case Noeud_MESURE:
            afficherA(expr->gauche);
            printf("|")
            if (expr->droit != NULL) {
                afficherA(expr->droit);
            }
            break;
        case Noeud_ID:
            printf("%s",expr->string);
            break;
        case Noeud_ENTIER:
            printf("%d", expr->valeur);
            break ;
	}
}
*/

// typedef enum {
//     Noeud_FICHIER, 
//     Noeud_PLAY, 
//     Noeud_AFF, 
//     Noeud_NOTE,
//     Noeud_SUITE_NOTE,
//     Noeud_DR, 
//     Noeud_MESURE,
//     Noeud_SEPMESURE, 
//     Noeud_ENTIER,
//     Noeud_OPERATION, 
//     Noeud_ID,
//     Noeud_JOINTURE,
//     Noeud_INST
// } TypeAst;

void evaluation(Ast melodie, double t) {
    if(A==NULL) {
        return;
    }
    switch(melodie.nature) {
        case Noeud_NOTE:
            double frq;
            frq = note_to_frequency(melodie.string, melodie.val);
            generate_signal
            break;

        case Noeud_MESURE:
            int dr = (A->gauche)->valeur;
        default:
            printf("ERREUR AST pas valide ! \n");
            exit(0);
        }

}

int calcul_nb_mesures(Ast A) {
    if(A==NULL) {
        return 0;
    }
    switch(A->nature) {
        case Noeud_MESURE:
            return 1;
        case Noeud_INST:
            return calcul_nb_mesures(A->gauche) + calcul_nb_mesures(A->droite);
        case Noeud_SEPMESURE:
            return calcul_nb_mesures(A->gauche) + calcul_nb_mesures(A->droite);
        case Noeud_AFF:
            return calcul_nb_mesures(A->droite);
        default:
            return 0;
    }
}