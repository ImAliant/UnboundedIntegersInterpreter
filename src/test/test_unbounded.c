#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    unbounded_int i1 = ll2unbounded_int(228886641);
    unbounded_int i2 = ll2unbounded_int(123);

    unbounded_int i3 = unbounded_int_produit(i1, i2);
    printf("%s\n", unbounded_int2string(i3));

    return 0;
}