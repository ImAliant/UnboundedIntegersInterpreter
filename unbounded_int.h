#ifndef _UNBOUNDED_INT_H_
#define _UNBOUNDED_INT_H_

typedef struct chiffre{
    struct chiffre *suivant; 
    char c;
    struct chiffre *precedent;
} chiffre;

typedef struct unbounded_int{
    char signe;       /* soit '+' soit '-' */
    size_t len;       /* longueur de la liste */
    chiffre *premier; /* pointeur vers le premier élément de la liste */
    chiffre *dernier; /* pointeur vers le dernier élément de la liste */
} unbounded_int;

// Prend une chaine de caractère en argument et renvoie un unbounded_int.
unbounded_int string2unbounded_int(const char *e);

// Prend un long long en argument et renvoie un unbounded_int.
unbounded_int ll2unbounded_int(long long i);

// Prend un unbounded_int en argument et renvoie une chaine de caractère.
char *unbounded_int2string(unbounded_int i);

// Compare deux unbounded_int et retourne -1, 0 ou 1 si a>b, a=b ou a<b.
int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b);

// Compare un unbounded_int et un entier long long et retourne -1, 0 ou 1 si a>b, a=b ou a<b.
int unbounded_int_cmp_ll(unbounded_int a, long long b);

// Retourne un unbounded_int qui correspondant a la somme des deux unbounded_int donnés en arguments.
unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);

// Retourne un unbounded_int qui correspond a la soustraction des deux unbounded_int donnés en arguments.
unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b);

// Retourne un unbounded_int qui correspond au produit des deux unbounded_int donnés en arguments.
unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b);

unbounded_int unbounded_int_puissance(unbounded_int a, unbounded_int b);

// Retourne un unbounded_int qui correspond au quotient de la division des deux unbounded_int donnés en arguments.
unbounded_int unbounded_int_quotient(unbounded_int a, unbounded_int b);

// Retourne un unbounded_int qui correspond au reste de la division des deux unbounded_int donnés en arguments.
unbounded_int unbounded_int_modulo(unbounded_int a, unbounded_int b);

#endif