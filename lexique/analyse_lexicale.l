%{

  /* types et variables utlisés par l'analyseur */

#include <stdio.h>
#include <stdlib.h>
#include "analyse_lexicale.h"

   unsigned int numcol=1 ; // numero de colonne courant

   Lexeme LC ;  // lexeme_courant

   /* fonction d'initialisation du lexème courant */
   void initLC () {
		strcpy(LC.chaine, yytext);
		LC.ligne=yylineno;
		LC.colonne=numcol;
		numcol=numcol+yyleng;
	      } ;
%}

%option yylineno   
%option noyywrap  

 /* expressions régulières définissant les catégories lexicales */

CHIFFRE [0-9]

ENTIER    {CHIFFRE}{CHIFFRE}*
OPERATEUR     [-+*/]
OPCOMP  "<"|">"|"<="|">="|"=="|"!="
PARO	  "("
PARF	  ")"
ACCO    "{"
ACCF    "}"

LETTRE [a-z]|[A-Z]|"à"|"é"|"è"|"ù"|"ç"
SEPINST ";"
SEPNOTE ","
SEPMESURE  "|"
AFF     "="

NOTE    ("C"|"D"|"E"|"F"|"G"|"A"|"B"){DIESE}?{ENTIER}

DIESE   "#"

INTERVALLE  ":"

COMMENTAIRE "/*"({LETTRE}|{CHIFFRE}|" "|":"|\n|","|"_"|"."|"=")*"*/"

DUREE_RYTHMIQUE   "dc"|"c"|"n"|"b"|"r"

ACCORD  @

PLAY  "play"

WHILE "while"

IF "if"

IDF    {LETTRE}({LETTRE}|{CHIFFRE}|"_")*


%%

  /* actions effectuées par l'analyseur lors de la reconnaissance d'un lexème */

 /* Pour les séparateurs on met juste à jour la valeur de numcol */
[ ]    {numcol = numcol + 1;}
[\t]   {numcol = numcol + 4;}
[\n]   {numcol = 1;}


 /* lexeme de type ENTIER */
{ENTIER}       {
		initLC() ;
		LC.nature = ENTIER; 
		LC.valeur=atoi(yytext);
		return 0 ;
		}

{OPERATEUR} {
  initLC();
  switch(yytext[0]) {
    case '+': LC.nature = PLUS; break;
    case '-': LC.nature = MOINS; break;
    case '*': LC.nature = MUL; break;
    case '/': LC.nature = DIV; break;
}
  return 0;
}

 /* lexeme de type OPCOMP */
{OPCOMP}  {
  initLC();
  switch(yytext[0]) {
    case '<':
      if(yytext[1]=='='){     /* INF STRICT (<) ou INF OU EG (<=) */
        LC.nature = INF_EG; break;
      }else{
        LC.nature = INF; break;
      }
    case '>': 
      if(yytext[1]=='='){     /* SUP STRICT (>) ou SUP OU EG (>=) */
        LC.nature = SUP_EG; break;
      }else{
        LC.nature = SUP; break;
      }
    case '=': 
      if(yytext[1]=='='){
        LC.nature = EG; break;
      }else{
        printf("ERREUR LEXICALE, found %s\n",LC.chaine); exit(0);
      }
    case '!': 
      if(yytext[1]=='='){
        LC.nature = DIFF; break;
      }else{
        printf("ERREUR LEXICALE, found %s\n",LC.chaine); exit(0);
      }
  }
  return 0;
}


 /* lexeme de type PARO */
{PARO} 	{ 
		initLC() ;
		LC.nature = PARO; 
		return 0 ;
		}

 /* lexeme de type PARF */
{PARF} 	{
		initLC() ;
		LC.nature = PARF; 
		return 0 ;
		}

 /* Lexeme de type ACCO */
{ACCO} 	{
		initLC() ;
		LC.nature = ACCO;
		return 0 ;
		}

 /* Lexeme de type ACCO */
{ACCF}  {
  initLC();
  LC.nature = ACCF;
  return 0;
}



 /* lexeme de type SEPINST */
{SEPINST} 	{
		initLC() ;
		LC.nature = SEPINST; 
		return 0 ;
		}


  /* lexeme de type SEPMES */ 
{SEPMESURE}  {
  initLC();
  LC.nature = SEPMESURE;
  return 0;
}

 /* lexeme de type AFF */
{AFF} 	{
		initLC() ;
		LC.nature = AFF; 
		return 0 ;
		}



 /* lexeme de type NOTE */
{NOTE} 	{
  initLC() ;
  LC.nature = NOTE;
  return 0 ;
}

 /* lexeme de type DIESE */
{DIESE} {
  initLC();
  LC.nature = DIESE;
  return 0;
}

 /* Lexeme de type INTERVALLE */
{INTERVALLE}  {
  initLC();
  LC.nature = INTERVALLE;
  return 0;
}

 /* lexeme de type SEPNOTE */
{SEPNOTE} {
  initLC();
  LC.nature = SEPNOTE;

  return 0;
}

 /* lexeme de type COMMENTAIRE */
{COMMENTAIRE} {
  initLC();
  LC.nature = COMMENTAIRE;
  return 0;
}

 /* Lexeme de type DUREE_RYTHMIQUE */
{DUREE_RYTHMIQUE} {
  initLC();
  LC.nature = DUREE_RYTHMIQUE;
  return 0;
}

 /* Lexeme de type ACCORD */
{ACCORD}  {
  initLC();
  LC.nature = ACCORD;
  return 0;
}


 /* Lexeme du mot-clé "play" */
{PLAY}  {
  initLC();
  LC.nature = PLAY;
  return 0;
}

 /* Lexeme du mot-clé "while" */
{WHILE} {
  initLC();
  LC.nature = WHILE;
  return 0;
}

 /* Lexeme du mot-clé "if" */
{IF} {
  initLC();
  LC.nature = IF;
  return 0;
}

 /* lexeme de type IDF */
{IDF} 	{
		initLC() ;
		LC.nature = IDF; 
		return 0 ;
		}

 /* lexeme de type FIN_DE_SEQUENCE  */
<<EOF>>     {
		initLC() ;	
		LC.nature=FIN_SEQUENCE ; 
		return 0 ;
            }
        


 /* Tous les autres cas  sont des erreurs lexicales  ...  */

.               {
		initLC() ;	
		LC.nature=ERREUR ;
		return 0 ;
	        }

%%

	/* fonctions auxilliaires fournies/utilisées par l'analyseur */

// renvoie la chaine de caracteres correspondant a la nature du lexeme
char *Nature_vers_Chaine (Nature_Lexeme nature) {
  switch (nature) {
    case ENTIER: return "ENTIER" ;
    case PLUS: return "PLUS" ;
    case MOINS: return "MOINS" ;
    case MUL: return "MUL" ;
    case DIV: return "DIV" ;
    case PARO: return "PARO" ;
    case PARF: return "PARF" ;
    case ACCO: return "ACCO";
    case ACCF: return "ACCF";
    case IDF: return "IDF" ;
    case SEPINST: return "SEPINST" ;
    case SEPNOTE: return "SEPNOTE";
    case SEPMESURE: return "SEPMESURE";
    case AFF: return "AFF" ;
    case FIN_SEQUENCE: return "FIN_SEQUENCE" ;


    case INF: return "INFÉRIEUR STRICT";
    case INF_EG: return "INFÉRIEUR OU ÉGALE";
    case SUP: return "SUPÉRIEUR STRICT";
    case SUP_EG: return "SUPÉRIEUR OU ÉGALES";
    case EG: return "ÉGALE";
    case DIFF: return "DIFFÉRENT";

    case COMMENTAIRE: return "COMMENTAIRE";

    case NOTE: return "NOTE";

    case DIESE: return "DIESE";
    case INTERVALLE: return "INTERVALLE";

    case DUREE_RYTHMIQUE: return "DUREE_RYTHMIQUE";

    case ACCORD: return "ACCORD";

    case PLAY: return "PLAY";
    case WHILE: return "WHILE";    
    case IF: return "IF";

    default: return "ERREUR" ;
  } ;
}

// affichage d'un lexème 
void afficher(Lexeme l) {

      switch (l.nature) {
         case FIN_SEQUENCE:
            break;
         default:
            printf("ligne: %d, ", l.ligne);
            printf("colonne: %d, ", l.colonne);
            printf("[") ;
            printf("nature = %s", Nature_vers_Chaine(l.nature)) ;
            printf(", chaine = %s", l.chaine) ;
            switch(l.nature) {
                 case ENTIER:
                      printf(", valeur = %d", l.valeur); break;

                 default:
                      break;
            } ;
            printf(" ]\n") ;
        } ;
   }


// lecture du lexeme suivant
void avancer() {
  yylex() ;  // fonction générée automatiquement !
} 

// valeur du lexeme courant
Lexeme lexeme_courant() {
  return LC ;
}

// fin de sequence de lexemes
int fin_de_sequence() {
      return lexeme_courant().nature == FIN_SEQUENCE;
}


// ouverture du fichier d'entrée (s'il existe)
void demarrer(char *nom_fichier) {
  if (strlen(nom_fichier) != 0) {
	yyin = fopen(nom_fichier, "r") ;
	if (!yyin) {
          printf("erreur ouverture fichier %s\n", nom_fichier) ;
	   exit(0) ;
       } 
  } ;
  avancer() ; // lecture du 1er lexeme
}

// fermeture du fichier d'entrée (s'il existe)
void arreter() {
	if (yyin != stdin) fclose(yyin) ;
}

