#ifndef _TYPE_AST_
#define _TYPE_AST_

typedef enum {
    Noeud_FICHIER, 
    Noeud_PLAY, 
    Noeud_AFF, 
    Noeud_NOTE,
    Noeud_SUITE_NOTE,
    Noeud_DR, 
    Noeud_MESURE,
    Noeud_SEPMESURE, 
    Noeud_ENTIER,
    Noeud_OPERATION, 
    Noeud_ID,
    Noeud_JOINTURE,
    Noeud_INST
} TypeAst;
typedef enum {N_SEPNOTE, N_ACCORD} TypeJointure;

typedef struct noeud {
    TypeAst nature;
    TypeJointure jointure;
    char* string;       // IDF/NOTE/DUREE_RYTHMIQUE/nom_fichier
    int valeur;
    struct noeud *gauche, *droite, *suite;
} NoeudAst;

typedef NoeudAst* Ast;

#endif