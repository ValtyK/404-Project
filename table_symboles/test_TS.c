#include <stdio.h>
#include "table_symboles.h"

int main() {
    char x[] = "{n(C4)}";
    char v[] = "r(A2, C#2)";
    char str[100];
    int val;
    int val_est_genti = 2424;
    double w;
    double wal = 42.443563;
    initTS();
    
    insererDoubleTS("x", wal);

    switch(estIntMelo("x")) {
        case 1:
            estPresentTS("x", str, &val, &w);
            printf("x = %d\nC'EST UN ENTIER MAIS NAN !\n", val);
            break;
        case 0:
            estPresentTS("x", str, &val, &w);
            printf("x = %s\nC'EST UN CHAR* MAIS NAN !\n", str);
            break;
        case -1:
            estPresentTS("x", str, &val, &w);
            printf("x = %f\n C'EST UN DOUBLE MAIS NAN !\n", w);
            break;    
    }

    
    afficheTS();
    insererIntTS("x",val_est_genti);
    afficheTS();

    if(estPresentTS("y", str, &val, &w)){
        printf("y? Oui je l'ai vu avec %s\n", str);
    }else{
        printf("y? Chépa\n");
    }
    
    insererMeloTS("x", v);
    insererMeloTS("y",x);
    afficheTS();
    insererIntTS("x", val_est_genti);

    if(estPresentTS("x", str, &val, &w)){
        printf("x? Oui je l'ai vu avec %d\n", val);
    }else{
        printf("x? Chépa\n");
    }


    return 0;
}
