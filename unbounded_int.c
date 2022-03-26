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
    if(virg != NULL)
        res.signe = '*';
    else{
        m = strstr(e, "-");
        if(m != NULL)
            res.signe = '-';
        else{
            res.signe = '+';
        }
    }

    chiffre * prem = malloc(sizeof(chiffre));
    prem->suivant = NULL;
    prem->precedent = NULL;
    int prem_ent;
    if(m != NULL) prem_ent = 1;
    else prem_ent =0;
    prem->c=e[prem_ent];

    res.premier = prem;
    res.dernier = prem;

    int len = strlen(e);
    int length = 0;

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

    ulltoa(i, s, 10);

    res = string2unbounded_int(s);

    return res;
}

char *unbounded_int2string(unbounded_int i) {
    char *res = malloc(i.len*sizeof(char)+1);
    assert(res != NULL);

    chiffre *cur = i.premier;

    int index;
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

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    char *sa = malloc(a.len*sizeof(char)+1);
    assert(sa != NULL);
    sa = unbounded_int2string(a);

    char *sb = malloc(b.len*sizeof(char)+1);
    assert(sb != NULL);
    sb = unbounded_int2string(b);

    int ia = atoi(sa);
    int ib = atoi(sb);
    
    int sum = ia + ib;

    char *ssum = malloc(sizeof(int)*a.len+b.len+1);
    itoa(sum, ssum, 10);

    res = string2unbounded_int(ssum);

    return res;
}

unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    char *sa = malloc(a.len*sizeof(char)+1);
    assert(sa != NULL);
    sa = unbounded_int2string(a);

    char *sb = malloc(b.len*sizeof(char)+1);
    assert(sb != NULL);
    sb = unbounded_int2string(b);

    int ia = atoi(sa);
    int ib = atoi(sb);

    int diff = abs(ia - ib);

    char *sdiff = malloc(sizeof(int)*a.len+b.len+1);
    itoa(diff, sdiff, 10);

    res = string2unbounded_int(sdiff);

    return res;
}

static int getSize(long long num) {
    int count = 0;
    while(num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

static long long karatsuba(long long i, long long j) {
    if(i < 10 && j < 10)
        return i * j;
    int size = fmax(getSize(i), getSize(j));

    int n = (int)ceil(size / 2.0);
    long long p = (long long)pow(10, n);
    long long a = (long long)floor(i / (double)p);
    long long b = i % p;
    long long c = (long)floor(j / (double)p); 
    long long d = j % p;

    long long ac = karatsuba(a, c);
    long long bd = karatsuba(b, d);
    long e = karatsuba(a + b, c + d) - ac - bd;

    return (long long)(pow(10 * 1LL, 2*n)*ac + pow(10*1LL, n)*e + bd);
}

unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b) {
    unbounded_int res;

    char *sa = malloc(a.len*sizeof(char)+1);
    assert(sa != NULL);
    sa = unbounded_int2string(a);

    char *sb = malloc(b.len*sizeof(char)+1);
    assert(sb != NULL);
    sb = unbounded_int2string(b);

    char *endptr;
    long long ia = strtoll(sa, &endptr, 10);
    long long ib = strtoll(sb, &endptr, 10);

    long long prod = karatsuba(ia, ib);

    res = ll2unbounded_int(prod);

    return res;
}