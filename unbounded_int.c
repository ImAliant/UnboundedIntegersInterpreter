#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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
}

static char * binaire(char *c) {
    long long nbr = atoi(c);
    int r = 0;
    int ord = 0;

    char *res = malloc(16*sizeof(char)+1);

    while(nbr != 0) {
        int reste = nbr%2;
        int p = (int)(pow(10, ord));
        r += reste * p;
        ord += 1;
        nbr /= 2;
    }

    sprintf(res, "%d", r);

    return res;
}

/*static int get_nb_bits(int nombre) {
    int bits=0;
    while(nombre)
    {
        nombre>>=1;
        bits++;
    }
    return bits;
}*/

//unbounded_int unbounded_int_quotient(unbounded_int a, unbounded_int b) {}

