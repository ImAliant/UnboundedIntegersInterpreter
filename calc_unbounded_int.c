#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "unbounded_int.h"

#define LINES_LENGTH 1024
#define VARIABLES 50
#define ATOM "%s"
#define BIN_OP "%s %c %s"
#define PRINT "print %s"

int i = 2;
char variables[VARIABLES];
unbounded_int valeur_variable[VARIABLES];

unbounded_int string2unbounded_int(const char *e) {
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

    sprintf(s, "%lld", i);
    
    res = string2unbounded_int(s);

    return res;
}

char *unbounded_int2string(unbounded_int i) {
    char *res;

    chiffre *cur = i.premier;

    unsigned int index;
    if(i.signe == '-') {
        res = malloc(i.len*sizeof(char)+1);
        assert(res != NULL);
        res[0] = i.signe;
        index = 1;
    }
    else {
        index = 0;
        res = malloc(i.len*sizeof(char));
        assert(res != NULL);
    }
    while(cur != NULL) {
        res[index] = cur->c;
        index++;
        cur = cur->suivant;
    }
    if (res[0] == '-')
        res[i.len + 1] = '\0';
    else res[i.len] = '\0';

    return res;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    int len_a = a.len;
    int len_b = b.len;
    int i;

    if (len_a > len_b) return 1;
    else if (len_a < len_b) return -1;
    else {
        char* sa = unbounded_int2string(a);
        char* sb = unbounded_int2string(b);

        for (i = 0; i < len_a; i++) {
            if ((sa[i] - '0') > (sb[i] - '0'))
                return 1;
            if ((sb[i] - '0') > (sa[i] - '0'))
                return -1;
        }
        if (i == len_a) return 0;
    }
}

int unbounded_int_cmp_ll(unbounded_int a, long long b) {
    unbounded_int uib = ll2unbounded_int(b);

    unbounded_int_cmp_unbounded_int(a, uib);
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
        int diff = abs(l_a - l_b);

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

    int diff = abs(a.len - b.len);

    if (a.signe == '+' && b.signe == '+') {
        int cmp = unbounded_int_cmp_unbounded_int(a, b);
        if (cmp == 1) {
            chiffre* cur_a = a.dernier;
            chiffre* cur_b = b.dernier;

            chiffre* cur = malloc(sizeof(chiffre));
            assert(cur != NULL);

            res.dernier = cur;
            cur->suivant = NULL;

            int r = 0;

            while (cur_a != NULL && cur_b != NULL) {
                int calc = (cur_a->c - '0') - (cur_b->c - '0') + r;
                cur->c = (calc >= 0) ? (char)(calc + '0') : (char)((calc + 10) + '0');
                r = (calc >= 0) ? 0 : -1;

                if (cur_a->precedent != NULL && cur_b->precedent != NULL) {
                    cur->precedent = malloc(sizeof(chiffre));
                    assert(cur->precedent);
                    cur->precedent->suivant = cur;
                    cur = cur->precedent;
                }

                cur_a = cur_a->precedent;
                cur_b = cur_b->precedent;
            }

            if (a.len > b.len) {
                while (cur_a != NULL && diff > 0) {
                    int calc = (cur_a->c - '0') + r;
                    
                    if(diff - 1 != 0) {
                        cur->precedent = malloc(sizeof(chiffre));
                        assert(cur->precedent);
                        cur->precedent->suivant = cur;
                        cur = cur->precedent;

                        cur->c = (calc >= 0) ? (char)(calc + '0') : (char)((calc + 10) + '0');
                        r = (calc >= 0) ? 0 : -1;
                    }
                    else {
                        if(calc > 0) {
                            cur->precedent = malloc(sizeof(chiffre));
                            assert(cur->precedent);
                            cur->precedent->suivant = cur;
                            cur = cur->precedent;

                            cur->c = (calc >= 0) ? (char)(calc + '0') : (char)((calc + 10) + '0');
                            r = (calc >= 0) ? 0 : -1;
                        }
                    }
                    
                    cur_a = cur_a->precedent;
                    diff--;
                }
            }
            if (a.len < b.len) {
                while (cur_b != NULL && diff > 0) {
                    int calc = (cur_b->c - '0') + r;
                    
                    if(diff - 1 != 0) {
                        cur->precedent = malloc(sizeof(chiffre));
                        assert(cur->precedent);
                        cur->precedent->suivant = cur;
                        cur = cur->precedent;

                        cur->c = (calc >= 0) ? (char)(calc + '0') : (char)((calc + 10) + '0');
                        r = (calc >= 0) ? 0 : -1;
                    }
                    else {
                        if(calc > 0) {
                            cur->precedent = malloc(sizeof(chiffre));
                            assert(cur->precedent);
                            cur->precedent->suivant = cur;
                            cur = cur->precedent;

                            cur->c = (calc >= 0) ? (char)(calc + '0') : (char)((calc + 10) + '0');
                            r = (calc >= 0) ? 0 : -1;
                        }
                    }

                    cur_b = cur_b->precedent;
                    diff--;
                }
            }

            while (cur->c == '0') {
                cur = cur->suivant;
                free(cur->precedent);
            }

            res.premier = cur;
            res.len = getSizeChaine(res);
            res.signe = '+';
        }
        else if(cmp == 0) {
            res = string2unbounded_int("0");
        }
        else {
            res = unbounded_int_difference(b, a);
            res.signe = '-';
        }
    }
    else {
        if (a.signe == '-' && b.signe == '-') {
            a.signe = '+';
            b.signe = '+';
            res = unbounded_int_difference(b, a);
        }
        else if (a.signe == '+' && b.signe == '-') {
            b.signe = '+';
            res = unbounded_int_somme(a, b);
        }
        else {
            a.signe = '+';
            res = unbounded_int_somme(b, a);
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
        if(i+1 < m+n) {
            dern->precedent = malloc(sizeof(chiffre));
            assert(dern->precedent != NULL);
            dern->precedent->suivant = dern;
            dern = dern->precedent;
        }
    }

    res.premier = dern;

    chiffre *cur_a;
    chiffre *cur_b;
    chiffre *cur_res = res.dernier;

    chiffre *temp = res.dernier;
    int r = 0;

    for(cur_b = b.dernier; cur_b != NULL; cur_b = cur_b->precedent) {
        r = 0;
        if(cur_b->c == '0') {
            cur_res = cur_res->precedent;
            temp = temp->precedent;
            continue;
        }
        for(cur_a = a.dernier; cur_a != NULL; cur_a = cur_a->precedent) {
            int v = (cur_res->c-'0') + (cur_a->c-'0')*(cur_b->c-'0') + r;
            cur_res->c = (char)((v%10)+'0');
            r = v/10;

            cur_res = cur_res->precedent;
        }
        if(r != 0)
            cur_res->c = r + '0';
        if(cur_b->precedent != NULL) {
            cur_res = temp->precedent;
            temp = temp->precedent;
        }
    }

    if(cur_res->c == '0') {
        res.premier = cur_res->suivant;
        free(cur_res);
        res.len = a.len+b.len-1;
    }
    else {
        res.premier = cur_res;
        res.len = a.len+b.len;
    }

    if((a.signe == '+' && b.signe == '+') || (a.signe == '-' && b.signe == '-'))
        res.signe = '+';
    else res.signe = '-';

    return res;
}

unbounded_int unbounded_int_quotient(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    unbounded_int temp_a = a;
    int compteur = -1;
    
    while (temp_a.signe != '-' || unbounded_int_cmp_ll(temp_a, 0) == 0) {
        temp_a = unbounded_int_difference(temp_a, b);
        compteur++;
    }

    res = ll2unbounded_int(compteur);

    return res;
}

unbounded_int unbounded_int_modulo(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    unbounded_int temp_a = a;
    
    while (temp_a.signe != '-' || unbounded_int_cmp_ll(temp_a, 0) == 0) {
        if (unbounded_int_cmp_ll(temp_a, 0) != 0)
            res = temp_a;
        temp_a = unbounded_int_difference(temp_a, b);
    }

    return res;
}

static int cherche_index_variable(char variable) {
    for(int i=0; i<VARIABLES; i++) {
        if(variables[i] == variable) {
            return i;
        }
    }
    return -1;
}

static void print_f_out(FILE* d, char c) {
    int index = cherche_index_variable(c);
    if(index == -1) {
        printf("Cette variable n'existe pas !");
        exit(1);
    }
    else {
        char* s = unbounded_int2string(valeur_variable[index]);
        if (!d) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fprintf(d, "%c = %s\n", c, s);
    }
}

static void addition(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
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
        printf("Une des variables n'existe pas !\n");
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
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else{
        if(unbounded_int_cmp_unbounded_int(valeur_variable[index_a], valeur_variable[index_b]) == -1)
            valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_b], valeur_variable[index_a]);
        else
            valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_a], valeur_variable[index_b]);
    }
        
}

static void division_quotient(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else {
        valeur_variable[index_variable] = unbounded_int_quotient(valeur_variable[index_a], valeur_variable[index_b]);
    }
}

static void division_modulo(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else {
        valeur_variable[index_variable] = unbounded_int_modulo(valeur_variable[index_a], valeur_variable[index_b]);
    }
}

static void condition_operation(char op, char var, char* var1, char* var2) {
    switch (op)
    {
    case '+':
        if(isdigit(var1[0]) && isdigit(var2[0]))
            addition(var, variables[0], variables[1]);
        else if(isdigit(var1[0]) && !isdigit(var2[0]))
            addition(var, variables[0], var2[0]);
        else if(!isdigit(var1[0]) && isdigit(var2[0]))
            addition(var, var1[0], variables[1]);
        else
            addition(var, var1[0], var2[0]);
        break;
    case '-':
        if(isdigit(var1[0]) && isdigit(var2[0]))
            soustration(var, variables[0], variables[1]);
        else if(isdigit(var1[0]) && !isdigit(var2[0]))
            soustration(var, variables[0], var2[0]);
        else if(!isdigit(var1[0]) && isdigit(var2[0]))
            soustration(var, var1[0], variables[1]);
        else
            soustration(var, var1[0], var2[0]);
        break;
    case '*':
        if(isdigit(var1[0]) && isdigit(var2[0]))
            multiplication(var, variables[0], variables[1]);
        else if(isdigit(var1[0]) && !isdigit(var2[0]))
            multiplication(var, variables[0], var2[0]);
        else if(!isdigit(var1[0]) && isdigit(var2[0]))
            multiplication(var, var1[0], variables[1]);
        else
            multiplication(var, var1[0], var2[0]);
        break;
    case '/':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            division_quotient(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            division_quotient(var, variables[0], var2[0]);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            division_quotient(var, var1[0], variables[1]);
        else
            division_quotient(var, var1[0], var2[0]);
        break;
    case '%':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            division_modulo(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            division_modulo(var, variables[0], var2[0]);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            division_modulo(var, var1[0], variables[1]);
        else
            division_modulo(var, var1[0], var2[0]);
        break;
    default:
        printf("Cette operation n'existe pas !");
        break;
    }
}

static void process_print(FILE* f, char var) {
    print_f_out(f, var);
}

static void process_atom(char v, char *var) {
    int index = cherche_index_variable(v);

    if (index == -1) {
        variables[i] = v;
        valeur_variable[i] = string2unbounded_int(var);
        i++;
    }
    else {
        valeur_variable[index] = string2unbounded_int(var);
    }
}

static void process_expression(char v, char* exp) {
    char* lhs = malloc(30 * sizeof(char));
    assert(lhs != NULL);
    char* rhs = malloc(30 * sizeof(char));
    assert(rhs != NULL);

    char* a = malloc(30 * sizeof(char));
    assert(a != NULL);
    char op = '0';

    if (sscanf(exp, BIN_OP, lhs, &op, rhs) == 3) {
        if (cherche_index_variable(v) == -1) {
            variables[i] = v;
            valeur_variable[i] = string2unbounded_int("0");
            i++;
        }

        if (isdigit(lhs[0]) || ((lhs[0] == '-' || lhs[0] == '+') && isdigit(lhs[1])))
            valeur_variable[0] = string2unbounded_int(lhs);
        if (isdigit(rhs[0]) || ((rhs[0] == '-' || rhs[0] == '+') && isdigit(rhs[1])))
            valeur_variable[1] = string2unbounded_int(rhs);

        if (lhs[0] == '-' || lhs[0] == '+')
            condition_operation(op, v, lhs + 1, rhs);
        else if (lhs[0] == '-' || rhs[0] == '+')
            condition_operation(op, v, lhs, rhs + 1);
        else if ((lhs[0] == '-' || lhs[0] == '+') && (rhs[0] == '-' || rhs[0] == '+'))
            condition_operation(op, v, lhs + 1, rhs + 1);
        else
            condition_operation(op, v, lhs, rhs);
    }
    else if (sscanf(exp, ATOM, a) == 1) {
        process_atom(v, a);
    }
    else {
        printf("ERROR : p_e");
        exit(EXIT_FAILURE);
    }
}

void interpreteur(char *source, char *dest) {
    FILE *fic_in = NULL;
    FILE* fic_out = NULL;

    if(strcmp(source, "vide") != 0) {
        fic_in = fopen(source, "r");
        if(fic_in == NULL) {
		    printf("Le fichier n'a pas pu etre ouvert.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
        fic_in = stdin;

    if (strcmp(dest, "vide") != 0) {
        fic_out = fopen(dest, "w+");
        if (fic_out == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }
    else
        fic_out = stdout;

    /*char var = 0;
    char op = 0;*/

    variables[0] = 'z'; //valeur temp 1
    valeur_variable[0] = string2unbounded_int("0");
    variables[1] = 'x'; //valeur temp 2
    valeur_variable[1] = string2unbounded_int("0");

    //SOLUTION PROF TD
    char op = '0';
    char var[128];

    char buffer[LINES_LENGTH];

    while (fgets(buffer, LINES_LENGTH, fic_in)) {
        char* lhs = malloc(30 * sizeof(char));
        assert(lhs != NULL);
        char* rhs = malloc(30 * sizeof(char));
        assert(rhs != NULL);
        
        if (sscanf(buffer, BIN_OP, lhs, &op, rhs) == 3) {
            if (op == '=')
                process_expression(lhs[0], rhs);
            else {
                printf("ERROR : 1 if");
                exit(EXIT_FAILURE);
            }
        }
        else if (sscanf(buffer, PRINT, var) == 1) {
            process_print(fic_out, var);
        }
        else {
            printf("ERROR : else");
            exit(EXIT_FAILURE);
        }
    }

    /*char* commande_ligne = malloc(LINES_LENGTH * sizeof(char));
    assert(commande_ligne != NULL);*/

    /*while(fgets(commande_ligne, LINES_LENGTH, fic_in) != NULL) {
        char* prt = strstr(commande_ligne, "print");
        if(prt != NULL) {
            var = commande_ligne[strlen(commande_ligne)-3]; //2 ou 3
            print(fic_out, var);
        }
        else {
            char * var1 = malloc(30*sizeof(char));
            assert(var1 != NULL);
            char * var2 = malloc(30*sizeof(char));
            assert(var2 != NULL);
            if(sscanf(commande_ligne, "%c = %s %c %s", &var, var1, &op, var2) == 4) {
                if(cherche_index_variable(var) == -1) {
                    variables[i] = var;
                    valeur_variable[i] = string2unbounded_int("0");
                    i++;
                }
                
                if(isdigit(var1[0]) || ((var1[0] == '-' || var1[0] == '+') && isdigit(var1[1])))
                    valeur_variable[0] = string2unbounded_int(var1);
                if(isdigit(var2[0]) || ((var2[0] == '-' || var2[0] == '+') && isdigit(var2[1])))
                    valeur_variable[1] = string2unbounded_int(var2);

                if(var1[0] == '-' || var1[0] == '+')
                    condition_operation(op, var, var1 + 1, var2);
                else if(var2[0] == '-' || var2[0] == '+')
                    condition_operation(op, var, var1, var2 + 1);
                else if((var1[0] == '-' || var1[0] == '+') && (var2[0] == '-' || var2[0] == '+'))
                    condition_operation(op, var, var1 + 1, var2 + 1);
                else
                    condition_operation(op, var, var1, var2);
            }
            else {
                char *ent = malloc(30*sizeof(char));
                assert(ent != NULL);
                if(sscanf(commande_ligne, "%c = %s", &var, ent) == 2) {
                    int index = cherche_index_variable(var);
                    if(index == -1) {
                        variables[i] = var;
                        valeur_variable[i] = string2unbounded_int(ent);
                        i++;
                    }
                    else {
                        valeur_variable[index] = string2unbounded_int(ent);
                    }
                }
            }
        }
    }*/
    
    fclose(fic_in);
    fclose(fic_out);
}

int main(int argc, char *argv[]) {
    char* source = malloc(10 * sizeof(char));
    assert(source != NULL);
    source = "vide";
    char *dest = malloc(10*sizeof(char));
    assert(dest != NULL);
    dest = "vide";

    if(argv[1] != NULL) {
        if(strcmp(argv[1], "-i") == 0)
            source = argv[2];
    
        if(strcmp(source, "vide") == 0) {
            if(strcmp(argv[1], "-o") == 0)
                dest = argv[2];
        }
        else {
            if(argv[3] != NULL) {
                if(strcmp(argv[3], "-o") == 0)
                    dest = argv[4];
            }
        }
    }
    
    interpreteur("source.txt", dest);

    return EXIT_SUCCESS;
}
