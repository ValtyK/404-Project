#ifndef _TYPE_AST_
#define _TYPE_AST_

typedef enum {N_NOTE, DR, VALEUR} typeAst;
typedef enum {N_C, N_D, N_E, N_F, N_G, N_A, N_B} typeNote;
typedef enum {N_dc, N_c, N_n, N_b, N_r} typeDureeRythmique;


typedef struct noeud {
    typeAst nature;
    typeNote note;
    typeDureeRythmique dr;
    struct noeud *gauche, *droite;
    int valeur;
} NoeudAst;

typedef NoeudAst* Ast;

#endif