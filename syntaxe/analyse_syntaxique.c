#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"


char* lexemeToString(Nature_Lexeme c) {
    switch (c) {
        case SEPMESURE: return "SEPMESURE";
        case ACCF:  return "ACCF";
        default:    return "INCONNU";;lj
    }
}

void rec_identifiant(Ast* A) {
    Ast A1, A2;
    
    facteur(&A1);
    if (lexeme_courant().nature != AFF) {
        printf("Erreur : '=' attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    switch (lexeme_courant().nature) {
        case ENTIER:
            A2 = creer_entier(lexeme_courant().valeur);
            *A = creer_operation(N_AFF, A1, A2);
            break;
        case ACCO:
            rec_melo(&A2);
            *A = creer_operation(N_AFF, A1, A2);
            break;
        default:
            printf("Erreur : ENTIER/melo attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
    }
}

void facteur(Ast* A1) {
    switch (lexeme_courant().nature) {
        case IDF:
            *A1 = creer_id(lexeme_courant().chaine);
            avancer();
            break;
        default:
            printf("Erreur : IDF attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
            exit(1);
    }
}

void rec_melo(Ast* A) {
    avancer();
    rec_seqmelo(&A);
    if (lexeme_courant().nature != ACCF) {
        printf("Erreur : parenthese fermante attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
}

void rec_seqmelo(Ast* A) {
    rec_mesure(Ast* A);
    if (lexeme_courant().nature != SEPMESURE) {
        printf("Erreur : '|' attendu après une mesure (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
        printf("lexeme_courant().nature = %s\n", lexemeToString(lexeme_courant().nature));
        exit(1);
    }
    rec_suite_seqmelo();
}

void rec_mesure(Ast* A) {
    Ast A1, A2;

    switch (lexeme_courant().chaine) {
        case "dc":
        case "c":
        case "n":
        case "b":
        case "r":
        default:
            printf("Erreur : DUREE_RYTHMIQUE attendu après une mesure (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
            exit(1);
    }

    *A = creer_mesure(A1, A2); // renvoie le sous arbre dans le resultat en parametre

    
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
    rec_identifiant(A);

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("Syntaxe : OK\n");
        afficherA(*A);
        printf("\n");
        return 1;
    } else {
        printf("Syntaxe : Erreur..\n");
        return 0;
    }
}