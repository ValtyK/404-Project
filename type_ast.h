#ifndef _TYPE_AST_
#define _TYPE_AST_

typedef enum {Noeud_NOTE, Noeud_DR, Noeud_MESURE, Noeud_ENTIER, Noeud_OPERATION} typeAst;

typedef struct noeud {
    typeAst nature;
    char* note;
    char* dr;
    char* idf;
    int valeur;
    struct noeud *gauche, *droite;
} NoeudAst;

typedef NoeudAst* Ast;

#endif