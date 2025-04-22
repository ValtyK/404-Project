#include <stdio.h>
#include "table_symbole.h"

int main() {
    char valeur[100];

    initTS();
    afficheTS();

    insererTS("x", "42");
    afficheTS();
    insererTS("y", "abc");

    if (estPresentTS("x", valeur)) {
        printf("x trouvé : %s\n", valeur);
    } else {
        printf("x non trouvé\n");
    }

    insererTS("x", "99");

    if (estPresentTS("x", valeur)) {
        printf("x MAJ : %s\n", valeur);
    }

    afficheTS();

    return 0;
}
