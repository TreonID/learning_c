#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long x, unsigned long long y) {
    unsigned long long q;
    assert(y != 0);
    do {
        q = x % y;
        x = y;
        y = q;
    } while (q != 0);
    return x;
}

unsigned long long lcm(unsigned long long a, unsigned long long b) {
    unsigned long long gcd_val = gcd(a, b);
    assert(gcd_val != 0);
    return a * b / gcd_val;
}

int main() {
    int res, n;
    unsigned long long lcm_acc = 2;
    res = scanf("%d", &n);
    if (res != 1) {
        fprintf(stderr, "Input error\n");
        abort();
    }

    for (int i = 2; i <= n; i++) {
        lcm_acc = lcm(lcm_acc, i);
    }
    printf("%llu\n", lcm_acc);
}