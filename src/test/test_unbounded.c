#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    unbounded_int a = string2unbounded_int("123456789");
    unbounded_int b = string2unbounded_int("00056789");
    unbounded_int c = string2unbounded_int("-1578");

    printf("a = %s\n", unbounded_int2string(a));
    printf("b = %s\n", unbounded_int2string(b));
    printf("c = %s\n", unbounded_int2string(c));

    return 0;
}