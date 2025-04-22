#include <stdio.h>
#include <stdlib.h>

#include "table_symbole.h"

extern void initTS(){
// intialise la TS en affectant 0 à NbSymb
    NbSumb = 0;
}


extern void afficheTS() {
// affiche le contenu complet de la TS 

}

extern int estPresentTS(char *idf, int *v) ;
// si un couple (idf, v') est present dans la table alors 
//      affecte v' à *v 
//      estPresentTS renvoie vrai
// sinon
//      estPresentTS renvoie faux

extern void insererTS(char *idf, int v) ;
// si un couple (idf,v') est present dans la table alors 
//      remplace la valeur v' par v 
// sinon
//      ajoute le couple (idf,v) dans la TS