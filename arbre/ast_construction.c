#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast_construction.h"
// Ast creer_operation(TypeOp op, Ast oprd_gauche, Ast oprd_droit){
//     Ast expr;
//     expr = (Ast) malloc (sizeof(NoeudAst));
//     expr->nature = Noeud_OPERATION;
//     expr->operateur = op;
//     if (oprd_gauche == NULL || oprd_droit == NULL) {
//         printf("ERREUR_EXPRESSION_ARBRE\n");
//         exit(1);
//     } else {
//         expr->gauche = oprd_gauche;
//         expr->droit = oprd_droit;
//     }
//     return expr;
// }

Ast creer_seqint(Ast A1, Ast A2) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_INST;
    expr->gauche = A1;
    expr->droite = A2;
    return expr;
}



Ast creer_play(Ast A1, Ast A2) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_PLAY;
    expr->gauche = A1;
    expr->droite = A2;
    return expr;
}

Ast creer_fichier(char* fichier) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_FICHIER;
    expr->string = fichier;
    return expr;
}

Ast creer_id(char* nom_variable) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_ID;
    expr->string = nom_variable;
    return expr;
}

Ast creer_seq_dr(Ast Adr, Ast Aseqnote, Ast Aseqdr) { // séquence de durée rythmique = mesure
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_SEQDR;
    if (Adr == NULL || Aseqnote == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE\n");
        exit(1);
    }
    expr->gauche = Adr;
    expr->droite = Aseqnote;
    expr->suite = Aseqdr;
    return expr;
}

Ast creer_sepmesure(Ast gauche, Ast droit) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_SEPMESURE;
    if (gauche == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE\n");
        exit(1);
    }
    expr->gauche = gauche;
    expr->droite = droit;
    return expr;
}

Ast creer_dr(char* duree_rythmique) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_DR;
    //expr->string = duree_rythmique;
    if(!strcmp(duree_rythmique, "dc")){
        expr->valeur = 16;
    } else if(!strcmp(duree_rythmique, "c")){
        expr->valeur = 8;
    } else if(!strcmp(duree_rythmique, "n")){
        expr->valeur = 4;
    } else if(!strcmp(duree_rythmique, "b")){
        expr->valeur = 2;
    }else{
        expr->valeur = 1;
    }
    return expr;
}

Ast creer_seq_note(Ast Anote, Ast Asuite_note) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_SEQNOTE;
    expr->gauche = Anote;
    expr->droite = Asuite_note;
    return expr;
}


Ast creer_note(char* note, int entier) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_NOTE;
    expr->string = note;
    expr->valeur = entier;
    return expr;
}

Ast creer_entier(int valeur) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_ENTIER;
    expr->valeur = valeur;
    return expr;
}

Ast creer_aff(Ast Ag, Ast Ad) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_AFF;
    expr->string = "=";
    if (Ag == NULL || Ad == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE\n");
        exit(1);
    }
    expr->gauche = Ag;
    expr->droite = Ad;
    return expr;
}