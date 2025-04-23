#include <stdio.h>
#include <stdlib.h>

Ast creer_operation(TypeOp op, Ast oprd_gauche, Ast oprd_droit){
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_OPERATION;
    expr->operateur = op;
    if (oprd_gauche == NULL || oprd_droit == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE")
        exit(1);
    } else {
        expr->gauche = oprd_gauche;
        expr->droit = oprd_droit;
    }
    return expr;
}


Ast creer_id(char* nom_variable) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_ID;
    expr->string = nom_variable;
}

Ast creer_mesure(Ast oprd_gauche, Ast oprd_droit) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_MESURE;
    if (oprd_gauche == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE")
        exit(1);
    }
    expr->gauche = oprd_gauche;
    expr->droit = oprd_droit;
}

Ast creer_dr(Ast oprd_gauche, Ast oprd_droit, char* duree_rythmique) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_DR;
    expr->string = duree_rythmique;
    if (oprd_gauche == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE")
        exit(1);
    }
    expr->gauche = oprd_gauche;
    expr->droit = oprd_droit;
}

Ast creer_note(char* note, Ast oprd_gauche, Ast oprd_droit) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_NOTE;
    expr->string = note;
    if (oprd_gauche == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE")
        exit(1);
    }
    expr->gauche = oprd_gauche;
    expr->droit = oprd_droit;
}

Ast creer_entier(int valeur) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_ENTIER;
    expr->valeur = valeur;
}