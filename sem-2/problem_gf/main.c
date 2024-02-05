#include <stdio.h>
#include <stdlib.h>

int main() {
    int res, n;
    res = scanf("%d", &n);
    if (res != 1) {
        fprintf(stderr, "Input error\n");
    }

    printf("N: %d\n", n);
}