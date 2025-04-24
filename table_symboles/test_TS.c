#include <stdio.h>
#include "table_symboles.h"

int main() {
    char x[] = "{n(C4)}";
    char v[] = "r(A2, C#2)";
    char str[100];
    int val;
    int val_est_genti = 2424;
    
    initTS();
    
    insererMeloTS("x", x);
    if(estIntMelo("x")) {
        estPresentTS("x", str, &val);
        printf("x = %d\nC'EST UN ENTIER MAIS NAN !\n", val);
    } else {
        estPresentTS("x", str, &val);
        printf("x = %s\nC'EST UN CHAR* MAIS NAN !\n", str);
    }
    
    
    afficheTS();
    insererIntTS("x",val_est_genti);
    afficheTS();

    if(estPresentTS("y", str, &val)){
        printf("y? Oui je l'ai vu avec %s\n", str);
    }else{
        printf("y? Chépa\n");
    }
    
    insererMeloTS("x", v);
    insererMeloTS("y",x);
    afficheTS();
    insererIntTS("x", val_est_genti);

    if(estPresentTS("x", str, &val)){
        printf("x? Oui je l'ai vu avec %d\n", val);
    }else{
        printf("x? Chépa\n");
    }


    return 0;
}
