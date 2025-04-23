#include <stdlib.h>
#include <stdio.h>


void aff_operateur(TypeOp op) {
	switch (op) {
		case N_AFF:
			printf(" = ") ;
			break;

	} 
}

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