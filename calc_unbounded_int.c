#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "unbounded_int.h"

#define LINES_LENGTH 1024
#define VARIABLES 50

char variables[VARIABLES];
unbounded_int valeur_variable[VARIABLES];

/*unbounded_int string2unbounded_int(const char *e) {
    unbounded_int res;

    char * virg = strstr(e, ",");
    char * m;
    char * p;
    if(virg != NULL)
        res.signe = '*';
    else{
        m = strstr(e, "-");
        p = strstr(e, "+");
        if(m != NULL)
            res.signe = '-';
        else{
            res.signe = '+';
        }
    }

    chiffre * prem = malloc(sizeof(chiffre));
    prem->suivant = NULL;
    prem->precedent = NULL;
    unsigned int prem_ent;
    if(m != NULL || p != NULL) prem_ent = 1;
    else prem_ent =0;
    prem->c=e[prem_ent];

    res.premier = prem;
    res.dernier = prem;

    unsigned int len = strlen(e);
    unsigned int length = 0;

    for(int i=prem_ent+1; i<len; i++){
        chiffre *n_elt = malloc(sizeof(chiffre));
        assert(n_elt != NULL);

        n_elt->c = e[i];
        n_elt->suivant = NULL;
        n_elt->precedent = res.dernier;
        res.dernier->suivant = n_elt;

        res.dernier = n_elt;
        length++;
    }
    res.len = length+1;

    return res;
}

unbounded_int ll2unbounded_int(long long i) {
    unbounded_int res;

    char *s = malloc(20*sizeof(long long)+1);
    assert(s != NULL);

    lltoa(i, s, 10);

    res = string2unbounded_int(s);

    return res;
}

char *unbounded_int2string(unbounded_int i) {
    char *res = malloc(i.len*sizeof(char)+1);
    assert(res != NULL);

    chiffre *cur = i.premier;

    unsigned int index;
    if(i.signe == '-') {
        res[0] = i.signe;
        index = 1;
    }
    else index = 0;
    while(cur != NULL) {
        res[index] = cur->c;
        index++;
        cur = cur->suivant;
    }
    res[i.len] = '\0';

    return res;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    char *sa = malloc(a.len*sizeof(char));
    assert(sa != NULL);
    sa = unbounded_int2string(a);

    char *sb = malloc(b.len*sizeof(char));
    assert(sb != NULL);
    sb = unbounded_int2string(b);

    int ia = atoi(sa);
    int ib = atoi(sb);

    if(ia < ib) return -1;
    else if(ia == ib) return 0;
    else return 1;
}

int unbounded_int_cmp_ll(unbounded_int a, long long b) {
    char *sa = malloc(a.len*sizeof(char));
    assert(sa != NULL);
    sa = unbounded_int2string(a);

    char *endptr;
    long long lla = strtoll(sa, &endptr, 10);

    if(lla < b) return -1;
    else if(lla == b) return 0;
    else return 1;
}

static int getSizeChaine(unbounded_int i) {
    int count = 0;
    chiffre *cur = i.premier;
    while(cur != NULL) {
        count++;
        cur = cur->suivant;
    }
    return count;
}

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    if((a.signe == '+' && b.signe == '+') || (a.signe == '-' && b.signe == '-')) {
        chiffre * dern = malloc(sizeof(chiffre));
        assert(dern != NULL);
        dern->suivant = NULL;
        dern->precedent = NULL;

        res.premier = dern;
        res.dernier = dern;

        int r = 0;
        chiffre *cur_a = a.dernier;
        chiffre *cur_b = b.dernier;
        chiffre *cur_res = res.dernier;
    
        while(cur_a != NULL && cur_b != NULL) {
            cur_res->c = (char)(((cur_a->c-'0')+(cur_b->c-'0')+r)%10 + '0');
            r = ((cur_a->c-'0')+(cur_b->c-'0')+r)/10;

            cur_res->precedent = malloc(sizeof(chiffre));
            assert(cur_res->precedent != NULL);
            cur_res->precedent->suivant = cur_res;
            cur_res = cur_res->precedent;
            cur_a = cur_a->precedent;
            cur_b = cur_b->precedent;
        }
        int l_a = a.len;
        int l_b = b.len;
        int diff = abs(a.len - b.len);

        int i;
        if(l_a < l_b) {
            i = 0;
            while(i < diff) {
                cur_res->c = (char)(((cur_b->c-'0')+r)%10 + '0'); 
                r = ((cur_b->c-'0')+r)/10;

                cur_res->precedent = malloc(sizeof(chiffre));
                assert(cur_res->precedent != NULL);
                cur_res->precedent->suivant = cur_res;
                cur_res = cur_res->precedent;
                cur_b = cur_b->precedent;
                i++;
            }
        }
        if(l_a > l_b) {
            i = 0;
            while(i < diff) {
                cur_res->c = (char)(((cur_a->c-'0')+r)%10 + '0'); 
                r = ((cur_a->c-'0')+r)/10;

                cur_res->precedent = malloc(sizeof(chiffre));
                assert(cur_res->precedent != NULL);
                cur_res->precedent->suivant = cur_res;
                cur_res = cur_res->precedent;
                cur_a = cur_a->precedent;
                i++;
            }
        }
        if(r>0) {
            cur_res->c = (char)(r+'0');
            res.premier = cur_res;
        }
        else {
            res.premier = cur_res->suivant;
            free(cur_res);
        }

        int length = getSizeChaine(res);
        res.len = length;
        if(a.signe == '+' && b.signe == '+')
            res.signe = '+';
        else res.signe = '-';
    }
    else {
        if(a.signe == '+' && b.signe == '-') {
            b.signe = '+';
            res = unbounded_int_difference(a, b);
        }
        else {
            a.signe = '+'; 
            res = unbounded_int_difference(b, a);
        }
        
    }
    
    return res;
}

unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    int l_a = a.len;
    int l_b = b.len;
    int diff = abs(a.len - b.len);
    
    if((a.signe == '+' && b.signe == '+') || (a.signe == '-' && b.signe == '-')) {
        chiffre * dern = malloc(sizeof(chiffre));
        assert(dern != NULL);
        dern->suivant = NULL;
        dern->precedent = NULL;

        res.premier = dern;
        res.dernier = dern;

        int r = 0;
        chiffre *cur_a = a.dernier;
        chiffre *cur_b = b.dernier;
        chiffre *cur_res = res.dernier;

        while(cur_a != NULL && cur_b != NULL) {
            int calc;
            if(l_a < l_b)
                calc = (cur_b->c - '0')-(cur_a->c - '0')+r;
            else calc = (cur_a->c - '0')-(cur_b->c - '0')+r;
            
            cur_res->c = (calc >= 0) ? (char)(calc+'0') : (char)((calc+10)+'0');
            r = (calc >= 0) ? 0 : -1;

            cur_res->precedent = malloc(sizeof(chiffre));
            assert(cur_res->precedent != NULL);
            cur_res->precedent->suivant = cur_res;
            cur_res = cur_res->precedent;
            cur_a = cur_a->precedent;
            cur_b = cur_b->precedent;
        }

        int i;
        if(l_a < l_b) {
            i = 0;
            while(i < diff) {
                cur_res->c = (char)(((cur_b->c-'0')+r) + '0'); 
                r = 0;

                cur_res->precedent = malloc(sizeof(chiffre));
                assert(cur_res->precedent != NULL);
                cur_res->precedent->suivant = cur_res;
                cur_res = cur_res->precedent;
                cur_b = cur_b->precedent;
                i++;
            }
        }
        if(l_a > l_b){
            i = 0;
            while(i < diff) {
                cur_res->c = (char)(((cur_a->c-'0')+r) + '0'); 
                r = 0;

                cur_res->precedent = malloc(sizeof(chiffre));
                assert(cur_res->precedent != NULL);
                cur_res->precedent->suivant = cur_res;
                cur_res = cur_res->precedent;
                cur_a = cur_a->precedent;
                i++;
            }
        }

        if(cur_res->suivant->c == '0') {
            res.premier = cur_res->suivant->suivant;
            free(cur_res->suivant);
            free(cur_res);
        }
        else {
            res.premier = cur_res->suivant;
            free(cur_res);
        }

        int length = getSizeChaine(res);
        res.len = length;
        if(a.signe == '+' && b.signe == '+') {
            if(b.len > a.len) res.signe = '-';
            else res.signe = '+';
        }
        else {
            if(b.len > a.len) res.signe = '+';
            else res.signe = '-';
        }
    }
    else {
        if(a.signe == '+' && b.signe == '-') {
            b.signe = '+';
            res = unbounded_int_somme(a, b);
        }
        else {
            a.signe = '+'; 
            res = unbounded_int_somme(a, b);
            res.signe = '-';
        }
    }

    return res;
}

unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    chiffre * dern = malloc(sizeof(chiffre));
    assert(dern != NULL);
    dern->suivant = NULL;
    dern->precedent = NULL;

    int m = a.len;
    int n = b.len;

    res.dernier = dern;

    for(int i = 0; i<m+n; i++) {
        dern->c = '0';
        dern->precedent = malloc(sizeof(chiffre));
        assert(dern->precedent != NULL);
        dern->precedent->suivant = dern;
        dern = dern->precedent;
    }

    res.premier = dern->suivant;

    chiffre *cur_a;
    chiffre *cur_b;
    chiffre *cur_res = res.dernier;

    int r;

    for(cur_b = b.dernier; cur_b != NULL; cur_b = cur_b->precedent) {
        r = 0;
        if(cur_b->c == '0') {
            cur_res = cur_res->precedent;
            continue;
        }
        for(cur_a = a.dernier; cur_a != NULL; cur_a = cur_a->precedent) {
            int v = (cur_res->c-'0') + (cur_a->c-'0')*(cur_b->c-'0') + r;
            cur_res->c = (char)((v%10)+'0');

            r = v/10;
            cur_res = cur_res->precedent;
        }
        cur_res = cur_res->suivant;
    }

    if(cur_res->c == '0') {
        free(cur_res);
        res.len = a.len+b.len-1;
    }
    else if(cur_res->c != '0' && r != 0){
        res.premier = cur_res->precedent;
        res.premier->c = (char)(r+'0');
        res.len = a.len+b.len;
    }
    else if(cur_res->c != '0' && r == 0){
        res.premier = cur_res;
        res.len = a.len+b.len;
    }

    if((a.signe == '+' && b.signe == '+') || (a.signe == '-' && b.signe == '-'))
        res.signe = '+';
    else res.signe = '-';

    return res;
}*/

static int cherche_index_variable(char variable) {
    int index = -1;
    for(int i=0; i<VARIABLES; i++) {
        if(variables[i] == variable) {
            index = i;
            break;
        }
    }
    return index;
}

static void print(char c) {
    int index = cherche_index_variable(c);
    if(index == -1) {
        printf("Cette variable n'existe pas !");
        exit(1);
    }
    else {
        printf("%s\n", unbounded_int2string(valeur_variable[index]));
    }
}

static void addition(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !");
        exit(1);
    }
    else {
        valeur_variable[index_variable] = unbounded_int_somme(valeur_variable[index_a], valeur_variable[index_b]);
    }
}

static void soustration(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !");
        exit(1);
    }
    else
        valeur_variable[index_variable] = unbounded_int_difference(valeur_variable[index_a], valeur_variable[index_b]);
}

static void multiplication(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !");
        exit(1);
    }
    else{
        if(unbounded_int_cmp_unbounded_int(valeur_variable[index_a], valeur_variable[index_b]) == -1)
            valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_b], valeur_variable[index_a]);
        else
            valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_a], valeur_variable[index_b]);
    }
        
}

void interpreteur() {
    FILE *instruc = fopen("source.txt", "r");
    if(instruc == NULL) {
		printf("Le fichier n'a pas pu être ouvert.\n");
        exit(1);
    }

    char var = 0;
    char * entier = malloc(20*sizeof(char));
    assert(entier != NULL);
    char op = 0;

    variables[0] = 'z'; //valeur temp 1
    valeur_variable[0] = string2unbounded_int("0");
    variables[1] = 'x'; //valeur temp 2
    valeur_variable[1] = string2unbounded_int("0");
    int i = 2;

    char *commande_ligne = malloc(1024*sizeof(char));
    assert(commande_ligne != NULL);

    while(fgets(commande_ligne, 1023, instruc) != NULL) {
        char *prt = strstr(commande_ligne, "print");
        if(prt != NULL) {
            var = commande_ligne[strlen(commande_ligne)-2];
            print(var);
        }
        else {
            long long e = 0;
            if(sscanf(commande_ligne, "%c = %lld", &var, &e) == 2) {
                int index = cherche_index_variable(var);
                if(index == -1) {
                    variables[i] = var;
                    valeur_variable[i] = ll2unbounded_int(e);
                    i++;
                }
                else {
                    valeur_variable[index] = ll2unbounded_int(e);
                }
            }
            else {
                char * var1 = malloc(20*sizeof(char));
                assert(var1 != NULL);
                char * var2 = malloc(20*sizeof(char));
                assert(var2 != NULL);
                if(sscanf(commande_ligne, "%c = %s %c %s", &var, var1, &op, var2) == 4) {
                    if(cherche_index_variable(var) == -1) {
                        variables[i] = var;
                        valeur_variable[i] = string2unbounded_int("0");
                        i++;
                    }
                    
                    /*printf("%c\n", var1[0]);
                    printf("%c\n", var2[0]);*/

                    if(isdigit(var1[0]))
                        valeur_variable[0] = string2unbounded_int(var1);
                    if(isdigit(var2[0]))
                        valeur_variable[1] = string2unbounded_int(var2);

                    if(op == '+') {
                        if(isdigit(var1[0]) && isdigit(var2[0]))
                            addition(var, variables[0], variables[1]);
                        else if(isdigit(var1[0]) && !isdigit(var2[0]))
                            addition(var, variables[0], var2[0]);
                        else if(!isdigit(var1[0]) && isdigit(var2[0]))
                            addition(var, var1[0], variables[1]);
                        else
                            addition(var, var1[0], var2[0]);
                    }
                    else if(op == '-') {
                        if(isdigit(var1[0]) && isdigit(var2[0]))
                            soustration(var, variables[0], variables[1]);
                        else if(isdigit(var1[0]) && !isdigit(var2[0]))
                            soustration(var, variables[0], var2[0]);
                        else if(!isdigit(var1[0]) && isdigit(var2[0]))
                            soustration(var, var1[0], variables[1]);
                        else
                            soustration(var, var1[0], var2[0]);
                    }
                    else if(op == '*'){
                        if(isdigit(var1[0]) && isdigit(var2[0]))
                            multiplication(var, variables[0], variables[1]);
                        else if(isdigit(var1[0]) && !isdigit(var2[0]))
                            multiplication(var, variables[0], var2[0]);
                        else if(!isdigit(var1[0]) && isdigit(var2[0]))
                            multiplication(var, var1[0], variables[1]);
                        else
                            multiplication(var, var1[0], var2[0]);
                    }
                    else printf("Cette operation n'existe pas !");
                }
            }
        }
    }
    fclose(instruc);
}

int main(int argc, char *argv[]) {
    /*char *source = malloc(10*sizeof(char));
    assert(source != NULL);*/

    //source = argv[2];
    
    interpreteur();

    return EXIT_SUCCESS;
}
