#ifndef _TYPE_AST_
#define _TYPE_AST_

typedef enum {Noeud_NOTE, Noeud_DR, Noeud_MESURE, Noeud_ENTIER, Noeud_OPERATION, Noeud_ID} TypeAst;
typedef enum {N_AFF} TypeOp;

typedef struct noeud {
    typeAst nature;
    TypeOp operateur;
    char* string;       // IDF/NOTE/DUREE_RYTHMIQUE
    int valeur;
    struct noeud *gauche, *droite;
} NoeudAst;

typedef NoeudAst* Ast;

#endif