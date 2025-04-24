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
            switch(TS[i].type) {
                case melo:
                    printf("IDF : %s\nContenu: %s\n\n",TS[i].nom, TS[i].melo);
                    break;
                case entier:
                    printf("IDF : %s\nContenu: %d\n\n",TS[i].nom, TS[i].valeur);
                    break;
                case doulbe:
                    printf("IDF : %s\nContenu: %f\n\n",TS[i].nom, TS[i].d_val);
                    break;
                default:
                    printf("ERREUR \n");
                    exit(0);
            }        
    }
    printf("FIN TABLE DES SYMBOLES\n");
}


int estIntMelo(char *idf) {
// Prend un couple (idf, v) 
//  renvoie 1 si type(v) = INT
//  renvoie 0 si type(v) = MELO (=STRING) 
//  renvoie -1 si type(v) = DOUBLE
    for(int i=0; i<NbSymb; i++) {
        if(strcmp(idf, TS[i].nom) == 0) {
            switch(TS[i].type) {
                case entier:
                    return 1;
                case melo:
                    return 0;
                case doulbe:
                    return -1;
                default:
                    printf("ERREUR pas de un type valide\n");
                    exit(0);
            }
        }
    }
    printf("ERREUR pas de un type valide\n");
    exit(0);
}

int estPresentTS(char *idf, char *u, int *v, double *w) {
// si un couple (idf, v') est present dans la table alors 
//      affecte v' à *u ou *v selon si c'est un STRING ou un INT
//      estPresentTS renvoie vrai
// sinon
//      estPresentTS renvoie faux
    for(int i=0; i<NbSymb; i++) {
        if(strcmp(idf, TS[i].nom) == 0) {
            switch(TS[i].type) {
                case entier:
                    *v = TS[i].valeur;
                    break;
                case melo:
                   strcpy(u, TS[i].melo);
                   break;
                case doulbe:
                    *w = TS[i].d_val;
                    break;
                default:
                    printf("ERREUR type pas valide\n");
                    exit(0);
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
            switch(TS[i].type) {
                case entier:
                    TS[i].type = melo;
                    TS[i].valeur = 0;
                    strcpy(TS[i].melo, v);
                    break;
                case doulbe:
                    TS[i].type = melo;
                    TS[i].d_val = 0.0;
                    strcpy(TS[i].melo, v);
                    break;
                case melo:
                    strcpy(TS[i].melo, v);
                    break;
                default:
                    printf("ERREUR pas de type valide\n");
                    exit(0);
            }
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
            switch(TS[i].type) {
                case melo:
                    TS[i].type = entier;
                    strcpy(TS[i].melo, "\0");
                    TS[i].valeur = v;
                    break;
                case doulbe:
                    TS[i].type = entier;
                    TS[i].d_val = 0.0;
                    TS[i].valeur = v;
                    break;
                case entier:
                    TS[i].valeur = v;
                    break;
                default:
                    printf("ERREUR pas de type valide\n");
                    exit(0);
            }
            return;
        }
    }
    strcpy(TS[NbSymb].nom, idf);
    TS[NbSymb].valeur = v;
    TS[NbSymb].type = entier;
    NbSymb++;
}

void insererDoubleTS(char *idf, double v) {

    for(int i=0; i<NbSymb; i++) {
        if (strcmp(idf, TS[i].nom) == 0) {

            switch(TS[i].type) {
                case melo:
                    TS[i].type = doulbe;
                    strcpy(TS[i].melo, "\0");
                    TS[i].d_val = v;
                    break;
                case entier:
                    TS[i].type = doulbe;
                    TS[i].valeur = 0;
                    TS[i].d_val = v;
                    break;
                case doulbe:
                    TS[i].d_val = v;
                    break;
                default:
                    printf("ERREUR pas de type valide\n");
                    exit(0);
            }
            return;
        }
    }
    strcpy(TS[NbSymb].nom, idf);
    TS[NbSymb].d_val = v;
    TS[NbSymb].type = doulbe;
    NbSymb++;
}

