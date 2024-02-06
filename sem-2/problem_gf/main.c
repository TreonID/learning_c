#include <stdio.h>
#include <stdlib.h>

int is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; ++i)
        if ((x % i) == 0) return 0;
    return 1;
}

int prime_seq(int a, int b) {
    int len = 0, n = 0;
    while (is_prime(n * n + a * n + b)) {
        ++len;
        ++n;
    }
    return len;
}

void check_generate(int n) {
    int max_a = 0, max_b = 0, max_seq = 0, seq = 0;
    for (int a = -n + 1; a < n; ++a) {
        for (int b = -n + 1; b < n; ++b) {
            seq = prime_seq(a, b);
            if (seq > max_seq) {
                max_seq = seq;
                max_a = a;
                max_b = b;
            }
        }
    }
    printf("%d %d %d\n", max_a, max_b, max_seq);
}

int main() {
    int res, n;
    res = scanf("%d", &n);
    if (res != 1) {
        fprintf(stderr, "Input error\n");
    }

    check_generate(n);
}