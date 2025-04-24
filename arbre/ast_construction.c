#include <stdio.h>
#include <stdlib.h>

// Ast creer_operation(TypeOp op, Ast oprd_gauche, Ast oprd_droit){
//     Ast expr;
//     expr = (Ast) malloc (sizeof(NoeudAst));
//     expr->nature = Noeud_OPERATION;
//     expr->operateur = op;
//     if (oprd_gauche == NULL || oprd_droit == NULL) {
//         printf("ERREUR_EXPRESSION_ARBRE");
//         exit(1);
//     } else {
//         expr->gauche = oprd_gauche;
//         expr->droit = oprd_droit;
//     }
//     return expr;
// }

Ast creer_seqint(Ast A1, A2) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_INST;
    
}

Ast creer_jointure_note(TypeJointure j) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_JOINTURE;
    expr->jointure = j;
    return expr;
}

Ast creer_play(Ast A1, Ast A2) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_PLAY;
    if (A1 == NULL, A2 == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE");
        exit(1);
    }
    expr->gauche = A1;
    expr->droit = A2;
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

Ast creer_mesure(Ast Adr, Ast Anote, Ast Asousmesure) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_MESURE;
    if (Adr == NULL || Anote == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE");
        exit(1);
    }
    expr->gauche = Adr;
    expr->droit = Anote;
    expr->suite = Asousmesure;
    return expr;
}

Ast creer_sepmesure(Ast gauche, Ast droit) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_SEPMESURE;
    if (oprd_gauche == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE");
        exit(1);
    }
    expr->gauche = oprd_gauche;
    expr->droit = oprd_droit;
    return expr;
}

Ast creer_dr(char* duree_rythmique) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_DR;
    expr->string = duree_rythmique;
    return expr;
}

Ast creer_seq_note(Ast Anote, Ast Asuite_note) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_SUITE_NOTE;
    expr->gauche = Anote;
    expr->droit = Asuite_note;
    return expr;
}

Ast creer_suite_note(Ast Aj, Ast Aseq_note) {
    Ast expr;
    expr = (Ast) malloc (sizeof(NoeudAst));
    expr->nature = Noeud_suite_seq_note;
    if (Aj == NULL) {
        printf("ERREUR_EXPRESSION_ARBRE");
        exit(1);
    }
    expr->gauche = Aj;
    expr->droit = Aseq_note;
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
        printf("ERREUR_EXPRESSION_ARBRE");
        exit(1);
    }
    expr->gauche = Ag;
    expr->droit = Ad;
    return expr;
}