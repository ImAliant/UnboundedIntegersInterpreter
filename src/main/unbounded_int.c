#include "unbounded_int.h"

#include <stdio.h>
#include <string.h>

#define POSITIVE 0
#define NEGATIVE 1

/* Vérifie si la chaîne de caractère donnée en argument est un entier */
static int check_integer(const char *e);
/* Vérifie si l'entier est négatif */
static int is_negative(const char *e);
/* Construit la liste de chiffre de l'unbounded_int retourné */
static void build_chiffre_list(unbounded_int *ui, const char *e);
/* Saute les zéros en début de chaîne */
static int skip_leading_zeros(const char *e, const unsigned int begin, const size_t len);
/* Initialise un chiffre */
static chiffre *init_chiffre(const char *e);

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

int unbounded_int_cmp_ll(const unbounded_int a, const long long b) {
    unbounded_int b_ui = ll2unbounded_int(b);
    
    return unbounded_int_cmp_unbounded_int(a, b_ui);
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
        chiffre *chiffre = init_chiffre(e);
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

chiffre *init_chiffre(const char *e) {
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