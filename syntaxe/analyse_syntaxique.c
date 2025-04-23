#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
char* couleurToString(Nature_Lexeme c) {
    switch (c) {
        case SEPMESURE: return "SEPMESURE";
        case ACCF:  return "ACCF";
        default:    return "INCONNU";
    }
}

void rec_melo() {
    rec_mea();
}

void rec_mea() {
    if (lexeme_courant().nature != ACCO) {
        printf("Erreur : parenthese ouvrante attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_seqmelo();
    if (lexeme_courant().nature != ACCF) {
        printf("Erreur : parenthese fermante attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
}

void rec_seqmelo() {  
    rec_mesure();
    if (lexeme_courant().nature != SEPMESURE) {
        printf("Erreur : '|' attendu après une mesure (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
        printf("lexeme_courant().nature = %s\n", couleurToString(lexeme_courant().nature));
        exit(1);
    }
    rec_suite_seqmelo();
}

void rec_mesure() {

    if (lexeme_courant().nature != DUREE_RYTHMIQUE) {
        printf("Erreur : DUREE_RYTHMIQUE attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    if (lexeme_courant().nature != PARO) {
        printf("Erreur : PARO attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_notes();
    if (lexeme_courant().nature != PARF) {
        printf("Erreur : PARF attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    rec_suite_seqmelo();
}

void rec_notes() {
    switch (lexeme_courant().nature) {
        case NOTE:
            avancer();
            if (lexeme_courant().nature != ENTIER) {
                printf("Erreur : ENTIER attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            avancer();
            rec_suite_notes();
            break;
        default:
            printf("Erreur : Une note est attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
            exit(1);
    }
}


void rec_suite_notes() {
    switch (lexeme_courant().nature) {
        case SEPNOTE:
        case ACCORD:
            avancer();
            rec_notes();
            break;
        default:
            break;
    }
}


void rec_suite_seqmelo() {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_seqmelo();
    }
}





// ------------------------------------------------------------------
int analyser(char* nomFichier) {
    demarrer(nomFichier);
    rec_melo();

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("\nSyntaxe : OK");
        printf("\n");
        return 1;
    } else {
        printf("Syntaxe : Erreur..");
        return 0;
    }
}