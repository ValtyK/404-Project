#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"


char* lexemeToString(Nature_Lexeme c) {
    switch (c) {
        case ENTIER: return "ENTIER";
        case ACCO: return "ACCO";
        case ACCF:  return "ACCF";
        case PARO: return "PARO";
        case PARF: return "PARF";
        case SEPINST: return "SEPINST";
        case AFF: return "AFF";
        case INF: return "INF";
        case INF_EG: return "INF_EG";
        case SUP: return "SUP";
        case SUP_EG: return "SUP_EG";
        case EG: return "EG";
        case DIFF: return "DIFF";
        case NOTE: return "NOTE";
        case DIESE: return "DIESE";
        case INTERVALLE: return "INTERVALLE";
        case SEPMESURE: return "SEPMESURE";
        case DUREE_RYTHMIQUE: return "DUREE_RYTHMIQUE";
        case VIRG: return "VIRG";
        case GUILLEMET: return "GUILLEMET";
        case COMMENTAIRE: return "COMMENTAIRE";
        case ACCORD: return "ACCORD";
        case PLAY: return "PLAY";
        case WHILE: return "WHILE";
        case IF: return "IF";
        case IDF: return "IDF";
        case ERREUR: return "ERREUR";
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
        avancer();
        //printf("%s\n", lexemeToString(lexeme_courant().nature));
        switch (lexeme_courant().nature) {
            case FIN_SEQUENCE:
                *A = A1;
                break;
            case COMMENTAIRE:
                avancer();
                suite_seq_inst(A1, A);
                break;
            default:
                rec_seq_inst(&A2);
                *A = creer_seqinst(A1, A2);
                break;
        }
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
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1); 
            }
            avancer();
            switch (lexeme_courant().nature) {
                case ENTIER:
                    Ad = creer_entier(lexeme_courant().valeur);
                    avancer();
                    break;
                case ACCO:
                    rec_melo(&Ad);
                    break;
                default:
                    printf("Erreur : type variable inconnu.. (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                    printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                    exit(1);
            }
            *A1 = creer_aff(Ag, Ad);
            break;
        case PLAY:
            avancer();
            if (lexeme_courant().nature != PARO) {
                printf("Erreur : PARO attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != IDF) {
                printf("Erreur : IDF attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }

            Ag = creer_id(lexeme_courant().chaine); // creation de l'arbre du premiere argument de play().
            
            avancer();
            if (lexeme_courant().nature != VIRG) {
                printf("Erreur : virgule attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != GUILLEMET) {
                printf("Erreur : guillemet attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != FICHIER) {
                printf("Erreur : nom de fichier attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }

            Ad = creer_fichier(lexeme_courant().chaine); // creation de l'arbre du second argument de play().
            *A1 = creer_play(Ag, Ad); // creation de du noeud play.

            avancer();
            if (lexeme_courant().nature != GUILLEMET) {
                printf("Erreur : GUIF attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }
            avancer();
            if (lexeme_courant().nature != PARF) {
                printf("Erreur : PARF attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }
            avancer();
            break;
        case COMMENTAIRE:
            printf("un commentaire dans inst\n");
            avancer();
            switch (lexeme_courant().nature) {
                case FIN_SEQUENCE:
                    *A1 = NULL;
                    break;
                default:
                    inst(A1);
                    break;
            }
            break;
        default:
            printf("Erreur : Une instruction ne peut commencer que par une fonction ou bien une affectation\n");
            printf("ligne %u, colonne %u\n", lexeme_courant().ligne, lexeme_courant().colonne);
            printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
            exit(1);
    }
}

void rec_melo(Ast* A) {
    if (lexeme_courant().nature != ACCO) {
        printf("Erreur : accolade ouvrante attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
        exit(1);
    }
    avancer();
    rec_seqmesure(A);
    if (lexeme_courant().nature != ACCF) {
        printf("Erreur : accolade fermante attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature)); 
        exit(1);
    }
    avancer();
}

void rec_seqmesure(Ast* A) {
    Ast A1, A2;
    rec_mesure(&A1);
    if (lexeme_courant().nature != SEPMESURE) {
        printf("Erreur : '|' attendu après une mesure (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
        exit(1);
    }
    rec_suite_seqmesure(&A2);
    *A = creer_sepmesure(A1, A2);
}

void rec_mesure(Ast* A) {
    Ast Adr, Aseq_note, Asousmesure;     // sous arbre ou arbre fils

    if (lexeme_courant().nature != DUREE_RYTHMIQUE) {
        printf("Erreur : DUREE_RYTHMIQUE attendu (ligne %u, colonne %u)\n", lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
        exit(1);
    }
    Adr = creer_dr(lexeme_courant().chaine);
    avancer();
    if (lexeme_courant().nature != PARO) {
        printf("Erreur : PARO attendu (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
        exit(1);
    }
    avancer();
    rec_seq_note(&Aseq_note);
    if (lexeme_courant().nature != PARF) {
        printf("Erreur : PARF attendu (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
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
            printf("note.chaine = %s\n", note);
            printf("ligne : %d / colonne : %d \n", lexeme_courant().ligne, lexeme_courant().colonne);
            avancer();
            if (lexeme_courant().nature != ENTIER) {
                printf("Erreur : ENTIER attendu (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
                printf("Lexeme actuel : %s\n", lexemeToString(lexeme_courant().nature));
                exit(1);
            }
            Anote = creer_note(note, lexeme_courant().valeur);
            avancer();
            rec_suite_notes(&Asuite_seq_note);
            break;
        default:
            printf("Erreur : Une note est attendue (ligne %u, colonne %u)\n",lexeme_courant().ligne, lexeme_courant().colonne);
            printf("Lexeme actuel : %s, chaine : %s\n", lexemeToString(lexeme_courant().nature), lexeme_courant().chaine);
            exit(1);
    }

    *A = creer_seq_note(Anote,Asuite_seq_note);
}


void rec_suite_notes(Ast* A) {
    switch (lexeme_courant().nature) {
        case VIRG:
            avancer();
            rec_seq_note(A);
            (*A)->jointure = N_VIRG;
            break;
        case ACCORD:
            avancer();
            rec_seq_note(A);
            (*A)->jointure = N_ACCORD;
            break;
        default:
            *A = NULL;
            break;
    }
}

void rec_suite_mesure(Ast* A) {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_mesure(A);
    }else{
        *A = NULL;
    }
}

void rec_suite_seqmesure(Ast* A) {
    avancer();
    if (lexeme_courant().nature == DUREE_RYTHMIQUE) {
        rec_seqmesure(A);
    }else{
        *A = NULL;
    }
}


// ------------------------------------------------------------------
int analyser(char* nomFichier, Ast* A) {

    demarrer(nomFichier);
    pgm(A);

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("Syntaxe : OK\n");
        //afficherA(*A);
        return 1;
    } else {
        printf("Syntaxe : Erreur..\n");
        printf("ligne %u, colonne %u\n", lexeme_courant().ligne, lexeme_courant().colonne);
        printf("Lexeme actuel : %s, chaine : %s\n", lexemeToString(lexeme_courant().nature), lexeme_courant().chaine);
        return 0;
    }
}