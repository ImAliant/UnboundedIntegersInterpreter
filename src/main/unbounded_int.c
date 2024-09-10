#include "unbounded_int.h"

#include <stdio.h>
#include <string.h>

#define POSITIVE 0
#define NEGATIVE 1

typedef int (*operation_func)(int, int, int *);

/* Vérifie si la chaîne de caractère donnée en argument est un entier */
static int check_integer(const char *e);
/* Vérifie si l'entier est négatif */
static int is_negative(const char *e);
/* Construit la liste de chiffre de l'unbounded_int retourné */
static void build_chiffre_list(unbounded_int *ui, const char *e);
/* Saute les zéros en début de chaîne */
static int skip_leading_zeros(const char *e, const unsigned int begin, const size_t len);
/* Saute les zéros pour un unbounded_int */
static unbounded_int skip_leading_zeros_ui(unbounded_int ui);
/* Initialise un chiffre */
static chiffre *init_chiffre();
/* Somme de deux unbounded_int */
static unbounded_int somme(unbounded_int a, unbounded_int b);
/* Soustraction de deux unbounded_int */
static unbounded_int difference(unbounded_int a, unbounded_int b);
/* Processus de somme ou de soustraction */
static unbounded_int process_unbounded_int(unbounded_int a, unbounded_int b, operation_func op);
/* Conversion int vers char */
static char int2char(int i);
/* Conversion char vers int */
static int char2int(char c);
/* Comparaison valeur absolue de deux unbounded_int */
static int unbounded_int_abs_cmp_unbounded_int(unbounded_int a, unbounded_int b);

/* Operation d'addition de deux unité */
static int add_digits(int digit_a, int digit_b, int *retenue);
/* Operation de soustraction de deux unité */
static int substract_digits(int digit_a, int digit_b, int *retenue);

unbounded_int string2unbounded_int(const char *e) {
    unbounded_int res;

    int is_integer = check_integer(e);
    if (!is_integer) {
        fprintf(stderr, "Erreur: la chaîne de caractère donnée n'est pas un entier\n");
        exit(EXIT_FAILURE);
    }

    build_chiffre_list(&res, e);

    return res;
}

unbounded_int ll2unbounded_int(const long long i) {
    unbounded_int res;

    char *e = malloc(sizeof(char) * 21);
    if (e == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (ll2unbounded_int)\n");
        exit(EXIT_FAILURE);
    }

    sprintf(e, "%lld", i);

    build_chiffre_list(&res, e);

    free(e);

    return res;
}

char *unbounded_int2string(const unbounded_int ui) {
    int offset = ui.signe;
    size_t len = ui.len;
    
    chiffre *premier = ui.premier;

    char *res = malloc(sizeof(char) * (len + offset + 1));
    if (res == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (unbounded_int2string) \n");
        exit(EXIT_FAILURE);
    }

    if (offset) {
        res[0] = '-';
    }

    int i = offset;
    for (; i < len + offset; i++) {
        res[i] = premier->c;
        premier = premier->suivant;
    }

    res[i] = '\0';

    return res;
}

int unbounded_int_cmp_unbounded_int(const unbounded_int a, const unbounded_int b) {
    if (a.signe > b.signe) return -1;
    if (a.signe < b.signe) return 1;

    if (a.len > b.len) return 1;
    if (a.len < b.len) return -1;

    chiffre *a_chiffre = a.premier;
    chiffre *b_chiffre = b.premier;

    size_t len = a.len > b.len ? a.len : b.len;

    for (size_t i = 0; i < len; i++) {
        if (a_chiffre->c > b_chiffre->c) return 1;
        if (a_chiffre->c < b_chiffre->c) return -1;

        a_chiffre = a_chiffre->suivant;
        b_chiffre = b_chiffre->suivant;
    }

    return 0;
}

int unbounded_int_abs_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    a.signe = POSITIVE;
    b.signe = POSITIVE;

    return unbounded_int_cmp_unbounded_int(a, b);
}

int unbounded_int_cmp_ll(const unbounded_int a, const long long b) {
    unbounded_int b_ui = ll2unbounded_int(b);
    
    return unbounded_int_cmp_unbounded_int(a, b_ui);
}

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    int compare_a = unbounded_int_cmp_ll(a, 0);
    int compare_b = unbounded_int_cmp_ll(b, 0);
    
    if (compare_a == -1 && compare_b == -1) {
        res = somme(a, b);
        res.signe = NEGATIVE;
    } else if (compare_a != -1 && compare_b == -1) {
        res = difference(a, b);
    } else if (compare_a == -1 && compare_b != -1) {
        res = difference(b, a);
    } else {
        res = somme(a, b);
    }

    return res;
}

unbounded_int somme(unbounded_int a, unbounded_int b) {
    return process_unbounded_int(a, b, add_digits);
}

unbounded_int difference(unbounded_int a, unbounded_int b) {
    return process_unbounded_int(a, b, substract_digits);
}

unbounded_int process_unbounded_int(unbounded_int a, unbounded_int b, operation_func op) {
    unbounded_int res;
    res.premier = NULL;
    res.dernier = NULL;
    res.signe = POSITIVE;
    res.len = 0;

    if (unbounded_int_abs_cmp_unbounded_int(a, b) == -1) {
        unbounded_int tmp = a;
        a = b;
        b = tmp;
        res.signe = NEGATIVE;
    }

    chiffre *curr_a = a.dernier;
    chiffre *curr_b = b.dernier;
    int retenue = 0;

    while (curr_a != NULL || curr_b != NULL || retenue != 0) {
        int digit_a = curr_a == NULL ? 0 : char2int(curr_a->c);
        int digit_b = curr_b == NULL ? 0 : char2int(curr_b->c);

        int digit_res = op(digit_a, digit_b, &retenue);

        chiffre *chiffre = init_chiffre();
        chiffre->c = int2char(digit_res);

        if (res.premier == NULL) {
            res.premier = chiffre;
            res.dernier = chiffre;
        } else {
            chiffre->suivant = res.premier;
            res.premier->precedent = chiffre;
            res.premier = chiffre;
        }

        if (curr_a != NULL) curr_a = curr_a->precedent;
        if (curr_b != NULL) curr_b = curr_b->precedent;

        res.len++;
    }

    res = skip_leading_zeros_ui(res);

    return res;
}

int add_digits(int digit_a, int digit_b, int *retenue) {
    int sum = digit_a + digit_b + *retenue;
    *retenue = sum / 10;
    return sum % 10;
}

int substract_digits(int digit_a, int digit_b, int *retenue) {
    digit_a += *retenue;

    if (digit_a < digit_b) {
        digit_a += 10;
        *retenue = -1;
    } else {
        *retenue = 0;
    }

    return digit_a - digit_b;
}

int char2int(char c) {
    return c - '0';
}

char int2char(int i) {
    return i + '0';
}

void build_chiffre_list(unbounded_int *ui, const char *e) {
    const unsigned int sign = is_negative(e);
    ui->signe = sign;

    int i = 0;
    if (ui->signe) {
        i++;
    }
    size_t integer_length = 0;
    size_t len = strlen(e);

    i = skip_leading_zeros(e, i, len);

    chiffre *current = NULL;
    chiffre *previous = NULL;

    for (; i < len; i++) {
        chiffre *chiffre = init_chiffre();
        chiffre->c = e[i];
        chiffre->precedent = previous;

        if (previous == NULL) {
            ui->premier = chiffre;
        } else {
            previous->suivant = chiffre;
        }

        previous = chiffre;
        current = chiffre;

        integer_length++;
    }

    ui->dernier = current;
    ui->len = integer_length;
}

int skip_leading_zeros(const char *e, const unsigned int begin, const size_t len) {
    int i = begin;
    for (; i < len; i++) {
        if (e[i] != '0') {
            break;
        }
    }
    return i;
}

unbounded_int skip_leading_zeros_ui(unbounded_int ui) {
    chiffre *current = ui.premier;
    while (current->c == '0' && ui.len > 1) {
        chiffre *tmp = current;
        current = current->suivant;
        current->precedent = NULL;
        free(tmp);
        ui.len--;
    }
    ui.premier = current;
    return ui;
}

chiffre *init_chiffre() {
    chiffre *chiffre = malloc(sizeof(chiffre));
    if (chiffre == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (init_chiffre)\n");
        exit(EXIT_FAILURE);
    }
    chiffre->precedent = NULL;
    chiffre->suivant = NULL;

    return chiffre;
}

int check_integer(const char *e) {
    int i = 0;
    if (is_negative(e)) {
        i++;
    }
    for (; e[i] != '\0'; i++) {
        if (e[i] < '0' || e[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int is_negative(const char *e) {
    if (e[0] == '-') {
        return 1;
    }
    return 0;
}