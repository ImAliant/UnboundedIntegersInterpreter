#include "../main/unbounded_int.h"

#include <stdio.h>

#define TEST_STRING2INT 0
#define TEST_INT2STRING 1
#define TEST_LL2UNBOUNDED_INT 2
#define TEST_CMP 3
#define TEST_CMP_LL 4
#define TEST_SOMME 5
#define TEST_DIFFERENCE 6
#define TEST_PRODUIT 7
#define TEST_PUISSANCE 8
#define TEST_QUOTIENT 9
#define TEST_MODULO 10

#define INTEGER_SIZE 1024
#define INPUT_SIZE 10

#define EXIT "exit\n"

static void find_test(char input, char *a, char *b);
static void test_string2int(char *a, char *b);
static void test_int2string();
static void test_ll2unbounded_int();
static void test_cmp();
static void test_cmp_ll();
static void test_somme();
static void test_difference();
static void test_produit();
static void test_puissance();
static void test_quotient();
static void test_modulo();

int main(int argc, char **argv) {
    while (1) {
        printf("> Choisissez un test: \n");
        
        char input[INPUT_SIZE];
        if (fgets(input, INPUT_SIZE, stdin) == NULL) {
            fprintf(stderr, "Erreur: fgets\n");
            return EXIT_FAILURE;
        }

        if (strcmp(input, EXIT) == 0) {
            return EXIT_SUCCESS;
        }

        printf("> Test: %s\n", input);
        printf("> Entrez deux entiers: \n");

        char a[INTEGER_SIZE];
        char b[INTEGER_SIZE];

        if (fgets(a, INTEGER_SIZE, stdin) == NULL) {
            fprintf(stderr, "Erreur: fgets\n");
            return EXIT_FAILURE;
        }
        if (fgets(b, INTEGER_SIZE, stdin) == NULL) {
            fprintf(stderr, "Erreur: fgets\n");
            return EXIT_FAILURE;
        }

        find_test(input, a, b);
    }
}

void test_string2int(char *a, char *b) {
    unbounded_int a_val = string2unbounded_int(a);
    unbounded_int b_val = string2unbounded_int(b);

    printf("> a: %s\n", unbounded_int2string(a_val));
    printf("> b: %s\n", unbounded_int2string(b_val));
}

void find_test(char input, char *a, char *b) {
    switch(input) {
        case TEST_STRING2INT:
            test_string2int(a, b);
            break;
        case TEST_INT2STRING:
            test_int2string();
            break;
        case TEST_LL2UNBOUNDED_INT:
            test_ll2unbounded_int();
            break;
        case TEST_CMP:
            test_cmp();
            break;
        case TEST_CMP_LL:
            test_cmp_ll();
            break;
        case TEST_SOMME:
            test_somme();
            break;
        case TEST_DIFFERENCE:
            test_difference();
            break;
        case TEST_PRODUIT:
            test_produit();
            break;
        case TEST_PUISSANCE:
            test_puissance();
            break;
        case TEST_QUOTIENT:
            test_quotient();
            break;
        case TEST_MODULO:
            test_modulo();
            break;
        default:
            fprintf(stderr, "Erreur: test non reconnu\n");
            break;
    }
}