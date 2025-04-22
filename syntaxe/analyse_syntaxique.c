#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"

    void rec_melo();
    void rec_mea();
    void rec_seqmelo();
    void rec_mesure();
    void rec_notes();
    void rec_suite_seqmelo();


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
}

void rec_seqmelo() {  
    rec_mesure();
    if (lexeme_courant().nature != SEPMESURE) {
        printf("Erreur : '|' attendu après une mesure (ligne %u, colonne %u)",lexeme_courant().ligne, lexme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_suite_seqmelo();
}

void rec_mesure() {

    lc = lexeme_courant().nature;

    if (lc != dc && lc != c && lc != n && lc != b && lc != r) {
        printf("Erreur : DUREE_RYTHMIQUE attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexme_courant().colonne);
        exit(1);
    }
    avancer();
    if (lc != PARO) {
        printf("Erreur : PARO attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_notes();
    if (lc != PARF) {dr &rarr; dc \
        printf("Erreur : PARF attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_suite_seqmelo();
}

void rec_notes() {
    switch (lexeme_courant().nature) {
        case C:
        case CDIESE:
        case D:
        case DDIESE:
        case E:
        case F:
        case FDIESE:
        case G:
        case GDIESE:
        case A:
        case ADIESE:
        case B:
            avancer();
            if (lexeme_courant().nature != ENTIER) {
                printf("Erreur : ENTIER attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexme_courant().colonne);
                exit(1);
            }
            avancer();
            rec_suite_notes();
        default:
            printf("Erreur : Une note est attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexme_courant().colonne);
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
    rec_seqmelo();
}



// ------------------------------------------------------------------
int analyer(char* nomFichier) {
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