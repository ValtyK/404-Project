#include <stdio.h>
#include <stdlib.h>

#include "table_symbole.h"

extern void initTS(){
// intialise la TS en affectant 0 à NbSymb
    NbSumb = 0;
}


extern void afficheTS() {
// affiche le contenu complet de la TS 
    for(int i=0; i<=NbSymb; i++){
        printf("IDF : %s\nContenu: %s\n\n",TS[i].nom, TS[i].melo);
    }
    printf("FIN TABLE DES SYMBOLES");
}

extern int estPresentTS(char *idf, char *v) {
// si un couple (idf, v') est present dans la table alors 
//      affecte v' à *v 
//      estPresentTS renvoie vrai
// sinon
//      estPresentTS renvoie faux
    for(int i=0; i<=NbSymb; i++) {
        if(idf==TS[i].nom) {
            *v = TS[i];
            return 1;
        }
    }
    return 0;
}

extern void insererTS(char *idf, char* v) {
// si un couple (idf,v') est present dans la table alors 
//      remplace la valeur v' par v 
// sinon
//      ajoute le couple (idf,v) dans la TS
    for(int i=0; i<=NbSymb; i++) {
        if(estPresentTS(TS[i].nom, TS[i].melo)) {
            TS[i].melo = v;
            return;
        }
    }
    TS[i].nom = nom;
    TS[i].melo = v;
    NbSymb++;

}