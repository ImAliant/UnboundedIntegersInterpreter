#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    unbounded_int i1 = ll2unbounded_int(5244);
    unbounded_int i2 = ll2unbounded_int(126);

    unbounded_int i3 = unbounded_int_quotient(i1, i2);
    printf("%s\n", unbounded_int2string(i3));

    return 0;
}