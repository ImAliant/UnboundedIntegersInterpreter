#include <stdlib.h>
#include <stdio.h>

#include "unbounded_int.h"

static void affiche(unbounded_int l){
    chiffre *cur;
    cur = l.premier;
    printf("[");
    while(cur != NULL) {
        if(cur->suivant == NULL){
            printf("%c", cur->c);
        }
        else {
            printf("%c ", cur->c);
        }
        cur = cur -> suivant;
    }
    printf("]\n longueur = %zu, signe = %c", l.len, l.signe);
}

int main(void) {
    const char *e = malloc(6*sizeof(char));
    e = "783592";

    unbounded_int s2ui = string2unbounded_int(e);
    //affiche(s2ui);

    long long i = 128430;
    unbounded_int ll2ui = ll2unbounded_int(i);
    //affiche(ll2ui);

    /*char *s = unbounded_int_int2string(ll2ui);
    printf("%s\n", s);*/

    //printf("%d\n", unbounded_int_cmp_unbounded_int(s2ui, s2ui));

    //long long j = 128431;
    //printf("%d\n", unbounded_int_cmp_ll(ll2ui, j));

    /*unbounded_int l_3 = unbounded_int_somme(s2ui, ll2ui);
    affiche(l_3);*/

    /*unbounded_int l_4 = unbounded_int_difference(s2ui, ll2ui);
    affiche(l_4);*/

    /*unbounded_int l_5 = unbounded_int_produit(s2ui, ll2ui);
    affiche(l_5);*/

    unbounded_int l_6 = unbounded_int_produit(s2ui,ll2ui);
    affiche(l_6);
    
    return EXIT_SUCCESS;
}


