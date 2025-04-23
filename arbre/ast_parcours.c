#include <stdlib.h>
#include <stdio.h>

#include "../type_ast.h"

void aff_operateur(TypeOp op){
	switch (op) {
		case N_AFF:
			printf(" = ") ;
			break;

	} 
}

void afficherA(Ast expr) {
	switch (expr->nature) {
        case OPERATION:
            printf("(");
            afficherA(expr->gauche);
            aff_operateur(expr->operateur) ;
            afficherA(expr->droite);
            printf(")");
            break ;
        case VALEUR:
            printf("%d", expr->valeur);
            break ;
	}
}