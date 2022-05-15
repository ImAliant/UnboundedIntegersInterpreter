#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "unbounded_int.h"

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

// Retourne le nombre d'�l�ment dans l'unbounded_int donn� en argument.
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

    //ACTUELLEMENT UTILISE

    chiffre* dern = malloc(sizeof(chiffre));
    assert(dern != NULL);
    dern->suivant = NULL;
    dern->precedent = NULL;

    int n = a.len;
    int m = b.len;
    int len_max = n + m;

    res.dernier = dern;

    for (int i = 0; i < len_max - 1; i++) {
        dern->c = '0';
        if (i + 1 < len_max - 1) {
            dern->precedent = malloc(sizeof(chiffre));
            assert(dern->precedent != NULL);
            dern->precedent->suivant = dern;
            dern = dern->precedent;
        }
    }

    res.premier = dern;

    chiffre* cur_a;
    chiffre* cur_b;
    chiffre* cur_res = res.dernier;

    chiffre* temp = res.dernier;
    int r = 0;

    for (cur_b = b.dernier; cur_b != NULL; cur_b = cur_b->precedent) {
        r = 0;
        if (cur_b->c == '0') {
            cur_res = cur_res->precedent;
            temp = temp->precedent;
            continue;
        }
        for (cur_a = a.dernier; cur_a != NULL; cur_a = cur_a->precedent) {
            int v = (cur_res->c - '0') + (cur_a->c - '0') * (cur_b->c - '0') + r;
            cur_res->c = (char)((v % 10) + '0');
            r = v / 10;

            if(cur_res->precedent != NULL)
                cur_res = cur_res->precedent;
        }
        
        if (cur_b->precedent != NULL) {
            if (r != 0)
                cur_res->c = (char)(r + '0');
            cur_res = temp->precedent;
            temp = temp->precedent;
        }
    }

    if (r != 0) {
        dern->precedent = malloc(sizeof(chiffre));
        assert(dern->precedent != NULL);
        dern->precedent->suivant = dern;
        dern = dern->precedent;
        dern->c = (char)(r + '0');
        res.premier = dern;
        res.len = len_max;
    }
    else
        res.len = len_max - 1;

    if ((a.signe == '+' && b.signe == '+') || (a.signe == '-' && b.signe == '-'))
        res.signe = '+';
    else res.signe = '-';

    return res;

    //FONCTIONNE UNE FOIS
    //FONCTIONNE POUR LES GRANDS NOMBRES

    /*chiffre* dern = malloc(sizeof(chiffre));
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

    return res;*/
}

unbounded_int unbounded_int_puissance(unbounded_int x, unbounded_int y) {
    unbounded_int res;
    unbounded_int temp = x;
    unbounded_int i = ll2unbounded_int(1);
    while(unbounded_int_cmp_unbounded_int(i, y) != 0) {
        temp = unbounded_int_produit(temp, x);
        i = unbounded_int_somme(i, ll2unbounded_int(1));
    }
    res = temp;
    return res;
}

unbounded_int unbounded_int_quotient(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    unbounded_int temp_a = a;
    unbounded_int temp_b = b;

    if (temp_a.signe == '-')
        temp_a.signe = '+';
    if (temp_b.signe == '-')
        temp_b.signe = '+';
    int compteur = -1;

    if (unbounded_int_cmp_ll(b, 0) == 0) {
        printf("Le diviseur est �gale � 0 !!");
        exit(EXIT_FAILURE);
    }

    while (temp_a.signe != '-' || unbounded_int_cmp_ll(temp_a, 0) == 0) {
        temp_a = unbounded_int_difference(temp_a, temp_b);
        compteur++;
    }

    res = ll2unbounded_int(compteur);
    if ((a.signe == '-' && b.signe == '+') || (a.signe == '+' && b.signe == '-'))
        res.signe = '-';

    return res;
}

unbounded_int unbounded_int_modulo(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    unbounded_int temp_a = a;
    unbounded_int temp_b = b;

    temp_a.signe = '+';
    temp_b.signe = '+';
   
    while (temp_a.signe != '-' || unbounded_int_cmp_ll(temp_a, 0) == 0) {
        if (unbounded_int_cmp_ll(temp_a, 0) == 1)
            res = temp_a;
        if (unbounded_int_cmp_unbounded_int(temp_a, temp_b) == -1)
            break;
        temp_a = unbounded_int_difference(temp_a, temp_b);
    }

    if (a.signe == '-' && b.signe == '-')
        res.signe = '-';
    else if (a.signe == '+' && b.signe == '-')
        res = unbounded_int_difference(res, temp_b);
    else if (a.signe == '-' && b.signe == '+')
        res = unbounded_int_difference(temp_b, res);

    return res;
}

