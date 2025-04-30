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

const char* type_ast_to_string(TypeAst x) {
    switch (x) {
        case Noeud_FICHIER:     return "Noeud_FICHIER";
        case Noeud_PLAY:        return "Noeud_PLAY";
        case Noeud_AFF:         return "Noeud_AFF";
        case Noeud_NOTE:        return "Noeud_NOTE";
        case Noeud_SEQNOTE:  return "Noeud_SEQNOTE";
        case Noeud_DR:          return "Noeud_DR";
        case Noeud_SEQDR:      return "Noeud_SEQDR";
        case Noeud_SEPMESURE:   return "Noeud_SEPMESURE";
        case Noeud_ENTIER:      return "Noeud_ENTIER";
        case Noeud_OPERATION:   return "Noeud_OPERATION";
        case Noeud_ID:          return "Noeud_ID";
        case Noeud_INST:        return "Noeud_INST";
        default:                return "Type inconnu";
    }
}


void evaluation_mesure(Ast seqdr, double* t) {
    // allocation de mes variables
    double dr;
    Ast* Pseqdr = &seqdr;
    Ast* n = malloc(sizeof(Ast));

    while (*Pseqdr != NULL) {
        dr = (double) (seqdr->gauche)->valeur;
        *n = seqdr->droite;        // n->nature = Noeud_SEQNOTE
        printf("Nature Noeud : %s\n",type_ast_to_string((*n)->gauche->nature));
        printf("premiere note : %s\n",(*n)->gauche->string);
        while(n != NULL){
            printf("------------------\n");
            printf("Nature Noeud : %s\n",type_ast_to_string((*n)->gauche->nature));
            printf("string : %s\n",(*n)->gauche->string);
            printf("octave : %d\n", (*n)->gauche->valeur);
            double frq = note_to_frequency((*n)->gauche->string, (*n)->gauche->valeur);
            double tfin = (1/dr)*4*(BPM/60) + *t;
            generate_signal(*t, tfin, frq, 3000.0, SAMPLE_RATE);
            printf("SIGNAL pour note\n");
            *t = tfin;
            *n = (*n)->droite;
        }
        *Pseqdr = (*Pseqdr)->suite;
    }
}

void evaluer_seq_mesure(Ast sepmesure, double* t){
    if(sepmesure != NULL){
        evaluation_mesure(sepmesure->gauche, t);      // Evaluation d'une mesure/sequence de durees rythmiques
        evaluer_seq_mesure(sepmesure->droite, t);     // Evaluation de la mesure suivante
    }
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
        case Noeud_INST:
            return calcul_nb_mesures(A->gauche) + calcul_nb_mesures(A->droite);
        case Noeud_SEPMESURE:
            return 1 + calcul_nb_mesures(A->droite);
        case Noeud_AFF:
            return calcul_nb_mesures(A->droite);
        default:
            return 0;
    }
}

int calcul_nb_notes(Ast A) {
    if(A==NULL) {
        return 0;
    }
    switch(A->nature) {
        case Noeud_INST:
            return calcul_nb_notes(A->gauche) + calcul_nb_notes(A->droite);
        case Noeud_AFF:
            return calcul_nb_notes(A->droite);
        case Noeud_SEPMESURE:
            return calcul_nb_notes(A->gauche) + calcul_nb_notes(A->droite);
        case Noeud_SEQDR:
            return calcul_nb_notes(A->droite) + calcul_nb_notes(A->suite);
        case Noeud_SEQNOTE:
            return 1 + calcul_nb_notes(A->droite);
        default:
            return 0;
    }
}