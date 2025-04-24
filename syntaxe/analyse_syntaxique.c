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

void pgm(Ast* A) {
    rec_seq_inst(A);
}

void rec_seq_inst(Ast* A) {
    Ast A1;
    inst(&A1);
    suite_seq_inst(A1, A);
}

void suite_seq_inst(Ast A1, Ast* A) {
    Ast A2;
    if (lexeme_courant().nature == SEPINST) {
        rec_seq_inst(&A2);
        *A = creer_seqint(A1, A2);
    } else {
        A = &A1;
    }
}

void inst(Ast* A1) {
    Ast Ag, Ad;
    switch (lexeme_courant().nature) {
        case IDF:
            Ag = creer_id(lexeme_courant().chaine); // creer un arbre gauche qui contient l'identificateur
            avancer();
            if (lexeme_courant().nature != AFF) {
                printf("Erreur : '=' attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1); 
            }
            avancer();
            switch (lexeme_courant().nature) {
                case ENTIER:
                    Ad = creer_entier(lexeme_courant().valeur);
                    break;
                case ACCO:
                    rec_melo(&Ad);
                    break;
                default:
                    printf("Erreur : type variable inconnu.. (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
                    exit(1);
            }
            *A1 = creer_aff(Ag, Ad);
            break;
        case PLAY:
            avancer();
            if (lexeme_courant().nature != PARO) {
                printf("Erreur : PARO attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != IDF) {
                printf("Erreur : IDF attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }

            Ag = creer_id(lexeme_courant().chaine); // creation de l'arbre du premiere argument de play().
            
            avancer();
            if (lexeme_courant().nature != SEPNOTE) {
                printf("Erreur : virgule attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != GUIO) {
                printf("Erreur : guillemet attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != IDF) {
                printf("Erreur : nom de fichier attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }

            Ad = creer_fichier(lexeme_courant().chaine); // creation de l'arbre du second argument de play().
            *A1 = creer_play(Ag, Ad); // creation de du noeud play.

            avancer();
            if (lexeme_courant().nature != GUIF) {
                printf("Erreur : GUIF attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != PARF) {
                printf("Erreur : PARF attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            avancer();
        case COMMENTAIRE:
            break;
        default:
            printf("Erreur : Une instruction ne peut commencer que par une fonction ou bien une affectation");
            exit(1);
    }
}

void rec_melo(Ast* A) {
    if (lexeme_courant().nature != ACCO) {
        printf("Erreur : accolade ouvrante attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_seqmesure(A);
    if (lexeme_courant().nature != ACCF) {
        printf("Erreur : accolade fermante attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
}

void rec_seqmesure(Ast* A) {
    Ast A1, A2;
    rec_mesure(&A1);
    if (lexeme_courant().nature != SEPMESURE) {
        printf("Erreur : '|' attendu après une mesure (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
        printf("lexeme_courant().nature = %s\n", lexemeToString(lexeme_courant().nature));
        exit(1);
    }
    rec_suite_seqmesure(&A2);
    *A = creer_sepmesure(A1, A2);
}

void rec_mesure(Ast* A) {
    Ast Adr, Aseq_note, Asousmesure;     // sous arbre ou arbre fils

    if (lexeme_courant().nature != DUREE_RYTHMIQUE) {
        printf("Erreur : DUREE_RYTHMIQUE attendu (ligne %u, colonne %u)", lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    Adr = creer_dr(lexeme_courant().chaine);
    avancer();
    if (lexeme_courant().nature != PARO) {
        printf("Erreur : PARO attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    avancer();
    rec_seq_note(&Aseq_note);
    if (lexeme_courant().nature != PARF) {
        printf("Erreur : PARF attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
        exit(1);
    }
    rec_suite_mesure(&Asousmesure);
    *A = creer_mesure(Adr, Aseq_note, Asousmesure);
}

void rec_seq_note(Ast* A) {
    Ast Anote, Asuite_seq_note;
    char* note;
    
    switch (lexeme_courant().nature) {
        case NOTE:
            note = lexeme_courant().chaine;
            avancer();
            if (lexeme_courant().nature != ENTIER) {
                printf("Erreur : ENTIER attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
                exit(1);
            }
            Anote = creer_note(note, lexeme_courant().valeur);
            avancer();
            rec_suite_notes(&Asuite_seq_note);
            break;
        default:
            printf("Erreur : Une note est attendu (ligne %u, colonne %u)",lexeme_courant().ligne, lexeme_courant().colonne);
            exit(1);
    }

    *A = creer_seq_note(Anote,Asuite_seq_note);
}


void rec_suite_notes(Ast* A) {
    Ast Aj, Aseq_note;
    switch (lexeme_courant().nature) {
        case SEPNOTE:
            Aj = creer_jointure_note(N_SEPNOTE);
            break;
        case ACCORD:
            Aj = creer_jointure_note(N_ACCORD);
            avancer();
            break;
        default:
            break;
    }
    rec_seq_note(&Aseq_note);
    *A = creer_suite_note(Aj, Aseq_note);
}

void rec_suite_mesure(Ast* A) {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_mesure(A);
    }
}

void rec_suite_seqmesure(Ast* A) {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_seqmesure(A);
    }
}


// ------------------------------------------------------------------
int analyser(char* nomFichier, Ast* A) {

    demarrer(nomFichier);
    pgm(A);

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("Syntaxe : OK\n");
        //afficherA(*A);
        printf("\n");
        return 1;
    } else {
        printf("Syntaxe : Erreur..\n");
        return 0;
    }
}