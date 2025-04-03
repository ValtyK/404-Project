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

    ACCORD, // -
    ERREUR // erreur lexicale
} Nature_Lexeme;