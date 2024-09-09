#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    long long i = 12;
    long long j = 0;
    long long k = -12;
    unbounded_int a = ll2unbounded_int(i);
    unbounded_int b = ll2unbounded_int(j);
    unbounded_int c = ll2unbounded_int(k);

    printf("a = %s\n", unbounded_int2string(a));
    printf("b = %s\n", unbounded_int2string(b));
    printf("c = %s\n", unbounded_int2string(c));

    printf("a > b: %d\n", unbounded_int_cmp_ll(a, j));
    printf("a > c: %d\n", unbounded_int_cmp_ll(a, k));
    printf("b > c: %d\n", unbounded_int_cmp_ll(b, k));
    printf("c < a: %d\n", unbounded_int_cmp_ll(c, i));
    printf("c < b: %d\n", unbounded_int_cmp_ll(c, j));
    printf("a == a: %d\n", unbounded_int_cmp_ll(a, i));

    return 0;
}