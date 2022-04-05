#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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
    printf("]\nlongueur = %zu, signe = %c\n", l.len, l.signe);
    printf("\n");
}

int main(void) {
    printf("\n");
    //TEST STRING -> UNBOUNDED_INT:
    /*printf("Test char* vers unbounded_int: \n");
    const char *e = malloc(6*sizeof(char));
    assert(e != NULL);
    e = "1150";
    unbounded_int l_1 = string2unbounded_int(e);
    affiche(l_1);

    printf("--------------------------------------------------\n\n");

    //TEST UNBOUNDED_INT -> STRING:
    printf("Test unbounded_int vers char*: \n");
    char *s = unbounded_int2string(l_1);
    printf("%s\n\n", s);

    printf("--------------------------------------------------\n\n");

    //TEST LONG LONG -> UNBOUNDED_INT:
    printf("Test long long vers unbounded_int: \n");
    long long i = 882;
    unbounded_int l_2 = ll2unbounded_int(i);
    affiche(l_2);

    printf("--------------------------------------------------\n\n");

    //TEST CMP_UNBOUNDED_INT:
    printf("Test comparaison unbounded_int: \n");
    printf("%d\n\n", unbounded_int_cmp_unbounded_int(l_1, l_2));

    printf("--------------------------------------------------\n\n");

    //TEST CMP_LL:
    printf("Test comparaison unbounded_int et long long: \n");
    long long j = 128431;
    printf("%d\n\n", unbounded_int_cmp_ll(l_2, j));

    printf("--------------------------------------------------\n\n");*/

    const char *e = malloc(6*sizeof(char));
    assert(e != NULL);
    e = "1150";
    unbounded_int l_1 = string2unbounded_int(e);
    affiche(l_1);
    long long i = 1150;
    unbounded_int l_2 = ll2unbounded_int(i);
    affiche(l_2);
    //TEST ADDITION : 
        //a, b >= 0:
        /*printf("Test somme (a, b >= 0): \n");
        unbounded_int add_1 = unbounded_int_somme(l_1, l_2);
        affiche(add_1);

        //a, b <= 0:
        printf("Test somme (a, b <= 0): \n");
        l_1.signe = '-';
        l_2.signe = '-';
        unbounded_int add_2 = unbounded_int_somme(l_1, l_2);
        affiche(add_2);

        //a >= 0, b < 0:
        printf("Test somme (a >= 0, b < 0): \n");
        l_1.signe = '+';
        l_2.signe = '-';
        unbounded_int add_3 = unbounded_int_somme(l_1, l_2);
        affiche(add_3);

        //b >= 0, a < 0:
        printf("Test somme (b >= 0, a < 0): \n");
        l_1.signe = '-';
        l_2.signe = '+';
        unbounded_int add_4 = unbounded_int_somme(l_1, l_2);
        affiche(add_4);

    printf("--------------------------------------------------\n\n");
    
    //TEST SOUSTRACTION:
        //a, b >= 0:
        printf("Test soustration (a, b >= 0): \n");
        l_1.signe = '+';
        l_2.signe = '+';
        unbounded_int sous_1 = unbounded_int_difference(l_1, l_2);
        affiche(sous_1);

        //a, b <= 0:
        printf("Test soustration (a, b <= 0): \n");
        l_1.signe = '-';
        l_2.signe = '-';
        unbounded_int sous_2 = unbounded_int_difference(l_1, l_2);
        affiche(sous_2);

        //a >= 0, b < 0:
        printf("Test soustration (a >= 0, b < 0): \n");
        l_1.signe = '+';
        l_2.signe = '-';
        unbounded_int sous_3 = unbounded_int_difference(l_1, l_2);
        affiche(sous_3);

        //b >= 0, a < 0:
        printf("Test soustration (b >= 0, a < 0): \n");
        l_1.signe = '-';
        l_2.signe = '+';
        unbounded_int sous_4 = unbounded_int_difference(l_1, l_2);
        affiche(sous_4);

    printf("--------------------------------------------------\n\n");*/

    //TEST MULTIPLICATION:
        //a, b >= 0:
        printf("Test produit (a, b >= 0): \n");
        l_1.signe = '+';
        l_2.signe = '+';
        unbounded_int prod_1 = unbounded_int_produit(l_1, l_2);
        affiche(prod_1);

        //a, b <= 0:
        printf("Test produit (a, b <= 0): \n");
        l_1.signe = '-';
        l_2.signe = '-';
        unbounded_int prod_2 = unbounded_int_produit(l_1, l_2);
        affiche(prod_2);

        //a >= 0, b < 0:
        printf("Test produit (a >= 0, b < 0): \n");
        l_1.signe = '+';
        l_2.signe = '-';
        unbounded_int prod_3 = unbounded_int_produit(l_1, l_2);
        affiche(prod_3);

        //b >= 0, a < 0:
        printf("Test produit (b >= 0, a < 0): \n");
        l_1.signe = '-';
        l_2.signe = '+';
        unbounded_int prod_4 = unbounded_int_produit(l_1, l_2);
        affiche(prod_4);

    //TEST QUOTIENT:
        //unbounded_int_quotient(l_1, l_2);

    return EXIT_SUCCESS;
}


