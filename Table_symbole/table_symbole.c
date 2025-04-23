#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table_symbole.h"

Couple TS[NBMAXSYMB];
int NbSymb = 0;

extern void initTS(){
// intialise la TS en affectant 0 à NbSymb
    NbSymb = 0;
}


extern void afficheTS() {
// affiche le contenu complet de la TS 
    for(int i=0; i<NbSymb; i++){
        printf("IDF : %s\nContenu: %s\n\n",TS[i].nom, TS[i].melo);
    }
    printf("FIN TABLE DES SYMBOLES\n");
}

extern int estPresentTS(char *idf, char *v) {
// si un couple (idf, v') est present dans la table alors 
//      affecte v' à *v 
//      estPresentTS renvoie vrai
// sinon
//      estPresentTS renvoie faux
    for(int i=0; i<=NbSymb; i++) {
        if (strcmp(idf, TS[i].nom) == 0) {
            strcpy(v, TS[i].melo);
            return 1;
        }
    }
    return 0;
}

extern void insererTS(char *idf, char *v) {
// si un couple (idf,v') est present dans la table alors 
//      remplace la valeur v' par v 
// sinon
//      ajoute le couple (idf,v) dans la TS
    for(int i=0; i<NbSymb; i++) {
        if (strcmp(idf, TS[i].nom) == 0) {
            strcpy(TS[i].melo, v);
            return;
        }
    }
    
    strcpy(TS[NbSymb].nom, idf);
    strcpy(TS[NbSymb].melo, v);
    NbSymb++;

}