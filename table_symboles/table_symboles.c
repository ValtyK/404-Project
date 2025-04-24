#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table_symboles.h"

Couple TS[NBMAXSYMB];
int NbSymb = 0;

void initTS(){
// intialise la TS en affectant 0 à NbSymb
    NbSymb = 0;
}


void afficheTS() {
// affiche le contenu complet de la TS 
    for(int i=0; i<NbSymb; i++){
        if(TS[i].type == melo) {
            printf("IDF : %s\nContenu: %s\n\n",TS[i].nom, TS[i].melo);
        } else {
            printf("IDF : %s\nContenu: %d\n\n",TS[i].nom, TS[i].valeur);
        }
    }
    printf("FIN TABLE DES SYMBOLES\n");
}


int estIntMelo(Couple idf) {
// Prend un couple (idf, v) 
//  renvoie 1 si type(v) = INT
//  renvoie 0 si type(v) = MELO (=STRING) 
    if(idf.type == entier) {
        return 1;
    } else {
        return 0;
    }
}

int estPresentTS(char *idf, char *u, int *v) {
// si un couple (idf, v') est present dans la table alors 
//      affecte v' à *u ou *v selon si c'est un STRING ou un INT
//      estPresentTS renvoie vrai
// sinon
//      estPresentTS renvoie faux
    for(int i=0; i<NbSymb; i++) {
        if (strcmp(idf, TS[i].nom) == 0) {
            if(TS[i].type == melo){
                strcpy(u, TS[i].melo);
            } else {
                *v = TS[i].valeur;
            }
            return 1;
        }
    }
    return 0;
}



void insererMeloTS(char *idf, char *v) {
// si un couple (idf,v') est present dans la table alors 
//      remplace la valeur v' par v 
// sinon
//      ajoute le couple (idf,v) dans la TS
    for(int i=0; i<NbSymb; i++) {
        if (strcmp(idf, TS[i].nom) == 0) {
            if(TS[i].type == entier) {
                TS[i].type = melo;
                TS[i].valeur = 0;
            }
            strcpy(TS[i].melo, v);
            return;
        }
    }
    strcpy(TS[NbSymb].nom, idf);
    strcpy(TS[NbSymb].melo, v);
    TS[NbSymb].type = melo;
    NbSymb++;
}

void insererIntTS(char *idf, int v) {
// si un couple (idf,v') est present dans la table alors 
//      remplace la valeur v' par v 
// sinon
//      ajoute le couple (idf,v) dans la TS
    for(int i=0; i<NbSymb; i++) {
        if (strcmp(idf, TS[i].nom) == 0) {
            if(TS[i].type == melo) {
                TS[i].type = entier;
                strcpy(TS[i].melo, "\0");
            }
            TS[i].valeur = v;
            return;
        }
    }
    strcpy(TS[NbSymb].nom, idf);
    TS[NbSymb].valeur = v;
    TS[NbSymb].type = entier;
    NbSymb++;
}