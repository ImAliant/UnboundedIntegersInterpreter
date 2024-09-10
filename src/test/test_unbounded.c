#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    unbounded_int i1 = ll2unbounded_int(150);
    unbounded_int i2 = ll2unbounded_int(-150);

    unbounded_int somme = unbounded_int_somme(i1, i2);

    printf("somme: %s\n", unbounded_int2string(somme));

    return 0;
}