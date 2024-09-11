#include "../main/unbounded_int.h"

#include <stdio.h>

int main(int argc, char **argv) {
    unbounded_int a = ll2unbounded_int(2);
    unbounded_int b = ll2unbounded_int(5);

    unbounded_int res = unbounded_int_somme(a, b);

    char *res_str = unbounded_int2string(res);
    printf("%s\n", res_str);

    return 0;
}