#include "type_ast.h"

//Ast creer_operation(TypeOp op, Ast oprd_gauche, Ast oprd_droit);
Ast creer_seqint(Ast A1, Ast A2);
Ast creer_jointure_note(TypeJointure j);
Ast creer_play(Ast A1, Ast A2);
Ast creer_fichier(char* fichier);
Ast creer_id(char* nom_variable);
Ast creer_mesure(Ast Adr, Ast Anote, Ast Asousmesure);
Ast creer_sepmesure(Ast gauche, Ast droit);
Ast creer_dr(char* duree_rythmique);
Ast creer_seq_note(Ast Anote, Ast Asuite_note);
Ast creer_suite_note(Ast Aj, Ast Aseq_note);
Ast creer_note(char* note, int entier);
Ast creer_entier(int valeur);
Ast creer_aff(Ast Ag, Ast Ad);