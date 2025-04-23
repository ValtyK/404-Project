#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"


char* lexemeToString(Nature_Lexeme c) {
    switch (c) {
        case SEPMESURE: return "SEPMESURE";
        case ACCF:  return "ACCF";
        default:    return "INCONNU";
    }
}

void rec_identifiant() {
    if (lexeme_courant().nature != IDF) {
        printf("Erreur : Identifiant attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    if (lexeme_courant().nature != AFF) {
        printf("Erreur : '=' attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    switch (lexeme_courant().nature) {
        case ENTIER:
            break;
        case ACCO:
            rec_melo();
            break;
        default:
            printf("Erreur : ENTIER/melo attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
    }
}


void rec_melo() {
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
        printf("lexeme_courant().nature = %s\n", lexemeToString(lexeme_courant().nature));
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
    rec_suite_mesure();
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

void rec_suite_mesure() {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_mesure();
    }
}

void rec_suite_seqmelo() {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_seqmelo();
    }
}





// ------------------------------------------------------------------
int analyser(char* nomFichier, Ast* A) {
    demarrer(nomFichier);
    rec_identifiant();

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("Syntaxe : OK\n");
        return 1;
    } else {
        printf("Syntaxe : Erreur..\n");
        return 0;
    }
}