#include "../lexique/analyse_lexicale.h"
#include "../arbre/ast_construction.h"

void pgm(Ast* A);
void rec_seq_inst(Ast* A);
void suite_seq_inst(Ast A1, Ast* A);
void inst(Ast* A1);
void rec_melo(Ast* A);
void rec_seqmesure(Ast* A);
void rec_mesure(Ast* A);
void rec_seq_note(Ast* A);
void rec_suite_notes(Ast* A);
void rec_suite_mesure(Ast* A);
void rec_suite_seqmesure(Ast* A);


int analyser(char* nomFichier, Ast* A);