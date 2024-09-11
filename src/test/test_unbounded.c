#include "../main/unbounded_int.h"

#include <stdio.h>
#include <string.h>

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

/* static void find_test(char *input, char *a, char *b);
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
static void test_modulo(); */

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

        
    }
}

/* void test_string2int(char *a, char *b) {
    unbounded_int a_val = string2unbounded_int(a);
    unbounded_int b_val = string2unbounded_int(b);

    printf("> a: %s\n", unbounded_int2string(a_val));
    printf("> b: %s\n", unbounded_int2string(b_val));
} */

/* void test_int2string() {}
void test_ll2unbounded_int() {}
void test_cmp() {}
void test_cmp_ll() {}
void test_somme() {}
void test_difference() {}
void test_produit() {}
void test_puissance() {}
void test_quotient() {}
void test_modulo() {}

void find_test(char *input, char *a, char *b) {} */