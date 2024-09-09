#ifndef _UNBOUNDED_INT_H_
#define _UNBOUNDED_INT_H_

#include <stdlib.h>

typedef struct chiffre {
    struct chiffre *suivant;
    char c;
    struct chiffre *precedent;
} chiffre;

typedef struct {
    char signe;       /* soit '+' soit '-' */
    size_t len;       /* longueur de la liste */
    chiffre *premier; /* pointeur vers le premier élément de la liste */
    chiffre *dernier; /* pointeur vers le dernier élément de la liste */
} unbounded_int;

/* Prend une chaîne de caractère en argument et renvoie un unbounded_int */
unbounded_int string2unbounded_int(const char *e);
/* Prend un long long en argument et renvoie un unbounded_int */
unbounded_int ll2unbounded_int(const long long i);
/* Prend un unbounded_int en argument et renvoie une chaîne de caractère */
char *unbounded_int2string(const unbounded_int i);
/* Compare deux unbounded_int et retourne -1, 0, 1 si a>b, a=b ou a<b */
int unbounded_int_cmp_unbounded_int(const unbounded_int a, const unbounded_int b);
/* Compare un unbounded_int et une entier long long et retourne -1, 0, 1 si a>b, a=b ou a<b */ 
int unbounded_int_cmp_ll(const unbounded_int a, const long long b);
/* Retourne un unbounded_int qui correspondent a la somme des deux unbounded_int donnés en arguments */
unbounded_int unbounded_int_somme(const unbounded_int a, const unbounded_int b);
/* Retourne un unbounded_int qui correspond a la soustraction des deux unbounded_int donnés en arguments */
unbounded_int unbounded_int_difference(const unbounded_int a, const unbounded_int b);
/* Retourne un unbounded_int qui correspond au produit des deux unbounded_int donnés en arguments */
unbounded_int unbounded_int_produit(const unbounded_int a, const unbounded_int b);
/* Retourne un unbounded_int qui correspond a a^b */
unbounded_int unbounded_int_puissance(const unbounded_int a, const unbounded_int b);
/* Retourne un unbounded_int qui correspond a a/b */
unbounded_int unbounded_int_quotient(const unbounded_int a, const unbounded_int b);
/* Retourne un unbounded_int qui correspond a a%b */
unbounded_int unbounded_int_modulo(const unbounded_int a, const unbounded_int b);

#endif