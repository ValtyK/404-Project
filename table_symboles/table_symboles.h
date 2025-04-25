#ifndef ___TS___
#define ___TS___

#define LIDF 50  // nombre maximum de caractéres pour un IDF 
#define NBMAXSYMB 100  // nombre maximum d'IDF 
#include "../arbre/type_ast.h"

typedef enum { 
   entier,
   melo,
   doulbe
} type_symbole;

typedef struct {
   char nom[LIDF] ; // nom d'un identificateur
   Ast melo; // Soit c'est un Ast
   int valeur;       // soit un entier
   double d_val;     // soit un double
   type_symbole type; // le type contenu dans la variable
} Couple;


void initTS();
// intialise la TS en effectant 0 à NbSymb

int estIntMelo(char *idf);
// Prend un couple (idf, v) 
//  renvoie 1 si type(v) = INT
//  renvoie 0 si type(v) = MELO
// renvoie -1 si type(v) = DOULBE

void afficheTS() ;
// affiche le contenu complet de la TS 

int estPresentTS(char *idf, Ast *u, int *v, double *w) ;
// si un couple (idf, v') est present dans la table alors 
//      affecte v' à *u ou *v selon si c'est un INT ou un STRING
//      estPresentTS renvoie vrai
// sinon
//      estPresentTS renvoie faux

void insererMeloTS(char *idf, Ast *v); // version avec un string à insérer
void insererIntTS(char *idf, int v); // version avec un int à insérer
void insererDoubleTS(char *idf, double v); // version avec un double à insérer
// si un couple (idf,v') est present dans la table alors 
//      remplace la valeur v' par v 
// sinon
//      ajoute le couple (idf,v) dans la TS


#endif