#include <stdio.h>

extern int is_prime(int x);

int main() {
    int x;
    scanf("%d", &x);
    printf("%d\n", is_prime(x));
}