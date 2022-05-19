#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "unbounded_int.h"

#define LENGTH_NB 512

//Fonction qui affiche le unbounded_int
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

//Main du fichier test_unbounded_int.c
int main(void) {
    system("clear");
    printf("\033[37m\n");
    char c1[LENGTH_NB];
    char c2[LENGTH_NB];
    printf("Deux nombres sont nécessaires pour effectuer les tests sur les unbounded_int.\n");
    printf("Veuillez saisir un nombre :\n");
    fgets(c1, LENGTH_NB, stdin);
    c1[strlen(c1)-1] = '\0';
    printf("Un autre :\n");
    fgets(c2, LENGTH_NB, stdin);
    c2[strlen(c2)-1] = '\0';

    printf("\n");
    //TEST char* -> UNBOUNDED_INT:
    printf("\033[32mTEST char* -> UNBOUNDED_INT:\033[37m \n");
    unbounded_int l_1 = string2unbounded_int(c1);
    affiche(l_1);

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    //TEST UNBOUNDED_INT -> char*:
    printf("\033[32mTEST UNBOUNDED_INT -> char*:\033[37m \n");
    char *s = unbounded_int2string(l_1);
    printf("%s\n\n", s);

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    //TEST LONG LONG -> UNBOUNDED_INT:
    printf("\033[32mTEST LONG LONG -> UNBOUNDED_INT:\033[37m \n");
    long long i = atoll(c2);
    unbounded_int l_2 = ll2unbounded_int(i);
    affiche(l_2);

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    //TEST CMP_UNBOUNDED_INT:
    printf("\033[32mTEST CMP_UNBOUNDED_INT:\033[37m \n");
    printf("%d\n\n", unbounded_int_cmp_unbounded_int(l_1, l_2));

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    char c3[LENGTH_NB];
    printf("Nous avons besoin d'un long long pour faire le test de unbounded_int_cmp_ll.\n");
    printf("Saissisez un nombre:\n");
    fgets(c3, LENGTH_NB, stdin);
    c3[strlen(c3)-1] = '\0';
    printf("\n");

    //TEST CMP_LL:
    printf("\033[32mTEST CMP_LL:\033[37m \n");
    long long l_3 = atoll(c3);
    printf("%d\n\n", unbounded_int_cmp_ll(l_2, l_3));

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    unbounded_int ui_1 = string2unbounded_int(c1);
    unbounded_int ui_2 = string2unbounded_int(c2);

    //TEST ADDITION : 
        //a, b >= 0:
        printf("\033[32mTEST SOMME (a, b >= 0): (%s + %s)\033[37m \n", c1, c2);
        unbounded_int add_1 = unbounded_int_somme(ui_1, ui_2);
        affiche(add_1);

        //a, b <= 0:
        printf("\033[32mTEST SOMME (a, b <= 0): (-%s + -%s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '-';
        unbounded_int add_2 = unbounded_int_somme(ui_1, ui_2);
        affiche(add_2);

        //a >= 0, b < 0:
        printf("\033[32mTEST SOMME (a >= 0, b < 0): (%s + -%s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '-';
        unbounded_int add_3 = unbounded_int_somme(ui_1, ui_2);
        affiche(add_3);

        //b >= 0, a < 0:
        printf("\033[32mTEST SOMME (b >= 0, a < 0): (-%s + %s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '+';
        unbounded_int add_4 = unbounded_int_somme(ui_1, ui_2);
        affiche(add_4);

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");
    
    //TEST SOUSTRACTION:
        //a, b >= 0:
        printf("\033[32mTEST SOUSTRACTION (a, b >= 0): (%s - %s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '+';
        unbounded_int sous_1 = unbounded_int_difference(ui_1, ui_2);
        affiche(sous_1);

        //a, b <= 0:
        printf("\033[32mTEST SOUSTRACTION (a, b <= 0): (-%s - -%s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '-';
        unbounded_int sous_2 = unbounded_int_difference(ui_1, ui_2);
        affiche(sous_2);

        //a >= 0, b < 0:
        printf("\033[32mTEST SOUSTRACTION (a >= 0, b < 0): (%s - -%s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '-';
        unbounded_int sous_3 = unbounded_int_difference(ui_1, ui_2);
        affiche(sous_3);

        //b >= 0, a < 0:
        printf("\033[32mTEST SOUSTRACTION (b >= 0, a < 0): (-%s - %s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '+';
        unbounded_int sous_4 = unbounded_int_difference(ui_1, ui_2);
        affiche(sous_4);

    printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    //TEST MULTIPLICATION:
        //a, b >= 0:
        printf("\033[32mTEST PRODUIT (a, b >= 0): (%s * %s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '+';
        unbounded_int prod_1 = unbounded_int_produit(ui_1, ui_2);
        affiche(prod_1);

        //a, b <= 0:
        printf("\033[32mTEST PRODUIT (a, b <= 0): (-%s * -%s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '-';
        unbounded_int prod_2 = unbounded_int_produit(ui_1, ui_2);
        affiche(prod_2);

        //a >= 0, b < 0:
        printf("\033[32mTEST PRODUIT (a >= 0, b < 0): (%s * -%s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '-';
        unbounded_int prod_3 = unbounded_int_produit(ui_1, ui_2);
        affiche(prod_3);

        //b >= 0, a < 0:
        printf("\033[32mTEST PRODUIT (b >= 0, a < 0): (-%s * %s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '+';
        unbounded_int prod_4 = unbounded_int_produit(ui_1, ui_2);
        affiche(prod_4);

        printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    //TEST QUOTIENT:
        //a, b >= 0
        printf("\033[32mTEST QUOTIENT (a, b >= 0): (%s / %s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '+';
        unbounded_int quot_1 = unbounded_int_quotient(ui_1, ui_2);
        affiche(quot_1);

        //a, b <= 0
        printf("\033[32mTEST QUOTIENT (a, b <= 0): (-%s / -%s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '-';
        unbounded_int quot_2 = unbounded_int_quotient(ui_1, ui_2);
        affiche(quot_2);

        //a >= 0, b < 0
        printf("\033[32mTEST QUOTIENT (a >= 0, b < 0): (%s / -%s)\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '-';
        unbounded_int quot_3 = unbounded_int_quotient(ui_1, ui_2);
        affiche(quot_3);

        //b >= 0, a < 0
        printf("\033[32mTEST QUOTIENT (b >= 0, a < 0): (-%s / %s)\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '+';
        unbounded_int quot_4 = unbounded_int_quotient(ui_1, ui_2);
        affiche(quot_4);

        printf("\033[31m*--------------------------------------------------*\033[37m\n\n");

    //TEST MODULO
        //a, b >= 0
        printf("\033[32mTEST MODULO (a, b >= 0): (%s [%s])\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '+';
        unbounded_int mod_1 = unbounded_int_modulo(ui_1, ui_2);
        affiche(mod_1);

        //a, b <= 0
        printf("\033[32mTEST MODULO (a, b <= 0): (-%s [-%s])\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '-';
        unbounded_int mod_2 = unbounded_int_modulo(ui_1, ui_2);
        affiche(mod_2);

        //a >= 0, b < 0
        printf("\033[32mTEST MODULO (a >= 0, b < 0): (%s [-%s])\033[37m \n", c1, c2);
        ui_1.signe = '+';
        ui_2.signe = '-';
        unbounded_int mod_3 = unbounded_int_modulo(ui_1, ui_2);
        affiche(mod_3);

        //b >= 0, a < 0
        printf("\033[32mTEST MODULO (b >= 0, a < 0): (-%s [%s])\033[37m \n", c1, c2);
        ui_1.signe = '-';
        ui_2.signe = '+';
        unbounded_int mod_4 = unbounded_int_modulo(ui_1, ui_2);
        affiche(mod_4);

    return EXIT_SUCCESS;
}


