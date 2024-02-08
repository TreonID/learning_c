#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
    int n;
    char *s;
};

void fill_sieve(struct sieve_t *sv) {
    for (int i = 2; i * i <= sv->n; ++i)
        if (sv->s[i] == 0)
            for (int j = 2; i * j <= sv->n; ++j)
                sv->s[i * j] = 1;
}

int is_prime(struct sieve_t sv, int x) {
    return (sv.s[x] == 1) ? 0 : 1;
}

int num_len(int x) {
    int res = 0;
    while (x != 0) {
        x = x / 10;
        res++;
    }
    return res;
}

int mult(int c) {
    int res = 1;
    for (int i = 0; i < c; ++i) {
        res = res * 10;
    }
    return res;
}

int len_swap(int x) {
    int len = num_len(x) - 1;
    return (len < 0) ? 0 : len;
}

int c_swap(int x) {
    int len = len_swap(x);
    int res = x / 10;
    res = res + (x % 10) * mult(len);
    return res;
}

int is_ccprime(struct sieve_t sieve, int x) {
    int n = x;
    int len = len_swap(x);
    int result = 1;

    result = is_prime(sieve, n) ? result : 0;
    for (int i = 0; i < len; ++i) {
        n = c_swap(n);
        result = is_prime(sieve, n) ? result : 0;
    }
    return result;
}

int find_cc(int start, struct sieve_t *sv) {
    if (is_ccprime(*sv, start)) return start;
    for (int i = 1; i <= start; i++) {
        if (is_ccprime(*sv, start + i)) return start + i;
        if (is_ccprime(*sv, start - i)) return start - i;
    }
    return 0;
}

int main() {
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));
    int res, n;
    int bound = 20000000;

    res = scanf("%d", &n);
    if (res != 1) {
        fprintf(stderr, "Input error\n");
        abort();
    }

    sv->n = bound;
    sv->s = calloc(bound, sizeof(char));
    fill_sieve(sv);
    printf("%d\n", find_cc(n, sv));
    free(sv);
}
