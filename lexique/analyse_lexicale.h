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
    PLUS,         // +
    MOINS,        // -
    MUL,          // *
    DIV,          // /
    ENTIER,       // sequence de chiffres
    PARO,         // (
    PARF,         // )
    ACCO,         // {
    ACCF,         // }
    SEPINST,      // ;
    AFF,          // =
    FIN_SEQUENCE, // pseudo lexeme ajoute en fin de sequence
//OPCOMP
    INF,          // <
    INF_EG,       // <=
    SUP,          // >
    SUP_EG,       // >=
    EG,           // ==
    DIFF,         // !=  
    NOTE,        // C, D, E, F, G, A, B
    DIESE,        // #
    INTERVALLE,   // :
    SEPMESURE,    // | séparateur de mesure
    DUREE_RYTHMIQUE, // dc, c, n, b, r
    SEPNOTE,    // ,
    COMMENTAIRE,    // /* blablabla */ ou //
    ACCORD, // @

// mots-clé
    PLAY,
    WHILE,
    IF,

    IDF,          // sequence de lettres/chiffres
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

