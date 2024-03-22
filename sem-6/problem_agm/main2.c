#include <stdio.h>

int foo(int *x, int y, int z) {
    int res = 0;
    int i;
    if (z == 0) return 0;
    i = z - 1;
    if (i < 0) return z;
    goto L4;
L5:
    x[i + 1] = z;
    i -= 1;
    if (i == 0) goto L1;
L4:
    z = x[i];
    res = i;
    if (z > y) goto L5;
    res += 1;
L1: 
    return res;
}

int foo2(int *x, int y, int z) {
    int i = z - 1;
    int res = i;
    if (z <= 0) return z;

    while (x[i] > y) {
        if (i != z-1) {
            x[i + 1] = z;
            i--;
            if (i == 0) return res;
        }
        z = x[i];
        res = i;
    }
    return res + 1;
}

int foo3(int *x, int y, int z) {
    if (z <= 0) return z;
    for (int i = z -1; i > 0; --i) {

    }
}

int main() {
    int x[10] = {1, 1, 3, 3, 4, 1, 9, 4, 9, 4};
    int y = 5;

    printf("%d\n", foo(x, 5, 10));
    for(int i = 0; i < 10; ++i) {
        printf("%d ", x[i]);
    }
    printf("\n");
    
    printf("%d\n", foo2(x, 5, 10));
}