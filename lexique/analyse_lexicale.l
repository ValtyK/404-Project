%{

  /* types et variables utlisés par l'analyseur */

#include <stdio.h>
#include <stdlib.h>
#include "analyse_lexical.h"

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
OPCOMP  '<<'|'>>'|'<='|'>='|'=='|'!='
PARO	  "("
PARF	  ")"
ACCO    "{"
ACCF    "}"

LETTRE [a-z]|[A-Z]
IDF    {LETTRE}({LETTRE}|{CHIFFRE}|"_")*
SEPINST ";"
AFF     "="

NOTE    'C'|'D'|'E'|'F'|'G'|'A'|'B'
DIESE   "#"

SEPNOTE ','

COMMENTAIRE "/*"({LETTRE}|{CHIFFRE}|" "|\n)*"*/"|"//"({LETTRE}|{CHIFFRE}|" ")*\n

DUREE_RYTHMIQUE   'd'|'c'|'n'|'b'|'r'

ACCORD  {NOTE}'-'{NOTE}('-'{NOTE})*

PLAY  'play'

WHILE 'while'

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
      if(yytext[1]=='<'){     /* INF STRICT (<<) ou INF OU EG (<=) */
        LC.nature = INF; break;
      }else{
        LC.nature = INF_EG; break;
      }
    case '>': 
      if(yytext[1]=='>'){     /* SUP STRICT (>>) ou SUP OU EG (>=) */
        LC.nature = SUP; break;
      }else{
        LC.nature = SUP_EG; break;
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

 /* lexeme de type IDF */
{IDF} 	{
		initLC() ;
		LC.nature = IDF; 
		return 0 ;
		}

 /* lexeme de type SEPINST */
{SEPINST} 	{
		initLC() ;
		LC.nature = SEPINST; 
		return 0 ;
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
  switch (yytext[0]) {
    case 'C' : LC.nature = C; break ;
    case 'D' : LC.nature = D; break ;
    case 'E' : LC.nature = E; break ;
    case 'F' : LC.nature = F; break ;
    case 'G' : LC.nature = G; break ;
    case 'A' : LC.nature = A; break ;
    case 'B' : LC.nature = B; break ;
  } ;
  return 0 ;
}

 /* lexeme de type DIESE */
{DIESE} {
  initLC();
  LC.nature = DIESE;
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
  switch (yytext[0]) {
    case 'd': 
      if(yytext[1]=='c'){
        LC.nature = D_CROCHE; break;
      }else{
        printf("ERREUR LEXICALE, found %s\n",LC.chaine); exit(0);
      }
    case 'c': LC.nature = CROCHE; break;
    case 'n': LC.nature = NOIR; break;
    case 'b': LC.nature = BLANCHE; break;
    case 'r': LC.nature = RONDE; break;
  }
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
    case IDF: return "IDF" ;
    case SEPINST: return "SEPINST" ;
    case AFF: return "AFF" ;
    case FIN_SEQUENCE: return "FIN_SEQUENCE" ;

    case C: return "DO";
    case D: return "RE";
    case E: return "MI";
    case F: return "FA";
    case G: return "SOL";
    case A: return "LA";
    case B: return "SI";

    case DIESE: return "DIESE";

    case D_CROCHE: return "DOUBLE_CROCHE";
    case CROCHE: return "CROCHE";
    case NOIR: return "NOIR";
    case BLANCHE: return "BLANCHE";
    case RONDE: return "RONDE";

    case ACCORD: return "ACCORD";

    case PLAY: return "play";
    case WHILE: return "while";    
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
            printf(", chaine = %s, ", l.chaine) ;
            switch(l.nature) {
                 case ENTIER:
                      printf("valeur = %d", l.valeur); break;
                 default:
                      break;
            } ;
            printf("]\n") ;
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

