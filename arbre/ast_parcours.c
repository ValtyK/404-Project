#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../lib/musique.h"
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

void evaluation_mesure(Ast mesure, double* t) {
    double dr = (double) (mesure->gauche)->valeur;
    printf("duree rythmique valeur : %f\n", dr);
    Ast n = mesure->droite;     // n -> (sequence de notes : Ast)
    while(n != NULL){
        double frq = note_to_frequency(n->gauche->string, n->gauche->valeur);
        printf("note : %s, octave : %d\n",n->gauche->string, n->gauche->valeur);
        double tfin = (1/dr)*4*(BPM/60) + *t;
        generate_signal(*t, tfin, frq, 3000.0, SAMPLE_RATE);
        //printf("SIGNAL pour note\n");
        *t = tfin;
        n = n->droite;
    }
}

void evaluer_seq_mesure(Ast melodie, double* t){
    if(melodie == NULL){
        //printf("NOEUD_SEPMESURE = NULL\n");
        return;
    }
    evaluation_mesure(melodie->gauche, t);
    evaluer_seq_mesure(melodie->droite, t);
}

void parcours(Ast melodie, double* t){
    if(melodie==NULL) {
        return;
    }
    switch(melodie->nature) {
        case Noeud_INST:
            parcours(melodie->gauche, t);
            parcours(melodie->droite, t);
            break;
        case Noeud_SEPMESURE:
            evaluer_seq_mesure(melodie, t);
            break;
        case Noeud_AFF:
            parcours(melodie->droite, t);
            break;
        default:
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