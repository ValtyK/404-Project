#include <stdio.h>
#include "table_symbole.h"

int main() {
    char x[] = "n(C4)";
    char v[] = "r(A2, C#2)";
    char val[100];
    initTS();
    
    
    insererTS("x", x);
    afficheTS();
    if(estPresentTS("y", val)){
        printf("y? Oui je l'ai vu\n");
    }else{
        printf("y? Chépa\n");
    }
    
    insererTS("x", v);
    insererTS("y",x);
    insererTS("z", "2424");
    afficheTS();
    return 0;
}
