#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    unbounded_int a = ll2unbounded_int(12);
    unbounded_int b = ll2unbounded_int(0);
    unbounded_int c = ll2unbounded_int(-12);

    printf("a = %s\n", unbounded_int2string(a));
    printf("b = %s\n", unbounded_int2string(b));
    printf("c = %s\n", unbounded_int2string(c));

    printf("a > b: %d\n", unbounded_int_cmp_unbounded_int(a, b));
    printf("a > c: %d\n", unbounded_int_cmp_unbounded_int(a, c));
    printf("b > c: %d\n", unbounded_int_cmp_unbounded_int(b, c));
    printf("c < a: %d\n", unbounded_int_cmp_unbounded_int(c, a));
    printf("c < b: %d\n", unbounded_int_cmp_unbounded_int(c, b));
    printf("a == a: %d\n", unbounded_int_cmp_unbounded_int(a, a));

    return 0;
}