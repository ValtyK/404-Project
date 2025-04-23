#include "../type_ast.h"

Ast creer_operation(TypeOp op, Ast oprd_gauche, Ast oprd_droit);
Ast creer_id(char* nom_variable);
Ast creer_mesure(Ast oprd_gauche, Ast oprd_droit);
Ast creer_dr(Ast oprd_gauche, Ast oprd_droit, char* duree_rythmique);
Ast creer_note(char* note, Ast oprd_gauche, Ast oprd_droit);
Ast creer_entier(int valeur);