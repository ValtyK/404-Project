/* ------------------------------------------------------------------------
-- analyse lexicale d'une suite de notes
--
-- Auteurs :
--      CARTALADE Mathéo
--      SLOTWINSKI Valentin
--      ROLAND Davin
--
-- Date création : 28 mars 2025
------------------------------------------------------------------------ */

typedef enum
{
    CHIFFRE,        // chiffre [0-9]
    SYMBOLE,        // symboles (#, |, les parenthèses/accolades, +-*/  <>=)
    LETTRE,         // lettres [a-z] ou [A-Z]
    C_FIN_SEQUENCE, // caractere de fin de sequence
    ERREUR_CAR      // caractere incorrect
} Nature_Caractere;

typedef enum
{
    ENTIER,       // sequence de chiffres
    PARO,         // (
    PARF,         // )
    ACCO,         // {
    ACCF,         // }
    IDF,          // sequence de lettres/chiffres
    SEPINST,      // ;
    AFF,          // :=
    FIN_SEQUENCE, // pseudo lexeme ajoute en fin de sequence
// Notes
    C,            // DO
    D,            // RÉ
    E,            // MI
    F,            // FA
    G,            // SOL
    A,            // LA
    B,            // SI
    SEPMESURE,    // | séparateur de mesure
// Durée rythmique
    D_CROCHE,   //dc
    CROCHE,  // c
    NOIR,    // n
    BLANCHE, // b
    RONDE,   // r

    ACCORD, // NOTE-NOTE-NOTE...

// mots-clé
    PLAY,
    WHILE,
    
    ERREUR // erreur lexicale
} Nature_Lexeme;

typedef struct
{
   Nature_Lexeme nature; // nature du lexeme
   unsigned int ligne;   // numero de ligne
   unsigned int colonne; // numero de colonne
   char chaine[256];     // chaine de caracteres
   int valeur;           // valeur d'un entier
} Lexeme;


// renvoie la chaine de caracteres correspondant a la nature du lexeme
char *Nature_vers_Chaine (Nature_Lexeme nature);

// affichage d'un lexème 
void afficher(Lexeme l);

// lecture du lexeme suivant
void avancer();

// valeur du lexeme courant
Lexeme lexeme_courant();

// fin de sequence de lexemes
int fin_de_sequence();

// ouverture du fichier d'entrée (s'il existe)
void demarrer(char *nom_fichier);

// fermeture du fichier d'entrée (s'il existe)
void arreter();

