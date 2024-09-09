#include "unbounded_int.h"

#include <stdio.h>
#include <string.h>

#define POSITIVE 0
#define NEGATIVE 1

/* Vérifie si la chaîne de caractère donnée en argument est un entier */
int check_integer(const char *e);
/* Renvoie le signe de l'entier */
int process_sign(const char *e);
/* Vérifie si l'entier est négatif */
int is_negative(const char *e);
/* Construit la liste de chiffre de l'unbounded_int retourné */
void build_chiffre_list(unbounded_int *ui, const char *e, const unsigned int sign);
/* Saute les zéros en début de chaîne */
int skip_leading_zeros(const char *e, const unsigned int begin, const size_t len);
/* Initialise un chiffre */
chiffre *init_chiffre(const char *e);

unbounded_int string2unbounded_int(const char *e) {
    unbounded_int res;

    int is_integer = check_integer(e);
    if (!is_integer) {
        fprintf(stderr, "Erreur: la chaîne de caractère donnée n'est pas un entier\n");
        exit(EXIT_FAILURE);
    }

    int sign = process_sign(e);
    res.signe = sign;

    build_chiffre_list(&res, e, sign);

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

void build_chiffre_list(unbounded_int *ui, const char *e, const unsigned int sign) {
    int i = 0;
    if (is_negative(e)) {
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

int process_sign(const char *e) {
    if (is_negative(e)) {
        return NEGATIVE;
    }
    return POSITIVE;
}

int is_negative(const char *e) {
    if (e[0] == '-') {
        return 1;
    }
    return 0;
}