#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};

struct sieve_t *GLOBAL_SV;
const int SIEVE_ARR_SIZE_IN_BYTES = 1000000;

void set_bit(unsigned char *s, int n) {
    unsigned byte_shift = n / 8;
    unsigned bit_n = n % 8;
    s[byte_shift] = s[byte_shift] | (1u << bit_n);
}

unsigned char get_bit(unsigned char *s, int n) {
    unsigned byte_shift = n / 8;
    unsigned bit_n = n % 8;
    return (s[byte_shift] >> bit_n) & 1u;
}

int is_prime_sieve(struct sieve_t *sv, unsigned n) {
    unsigned max_size = (sv->n * 8) * 6 + 5;
    int mod = n % 6;
    if (n == 2 || n == 3) return 1;
    if (n > max_size) {
        printf("Error: out of bounds, %d\n", n);
        return 0;
    }
    if (mod == 1)
        return (get_bit(sv->mod1, n / 6) == 1u) ? 0 : 1;
    if (mod == 5)
        return (get_bit(sv->mod5, n / 6) == 1u) ? 0 : 1;
    return 0;
}

void fill_sieve(struct sieve_t *sv) {
    int bound = (sv->n * 8) * 6;
    set_bit(sv->mod1, 0);
    for (int i = 2; i * i <= bound; ++i) {
        if (is_prime_sieve(sv, i))
            for (int j = 2; i * j <= bound; ++j) {
                if ((i * j - 1) % 6 == 0)
                    set_bit(sv->mod1, (i * j) / 6);
                else if ((i * j - 5) % 6 == 0)
                    set_bit(sv->mod5, (i * j) / 6);
            }
    }
}

unsigned long long gcd(unsigned long long x, unsigned long long y) {
    unsigned long long q, res;
    do {
        q = x % y;
        x = y;
        res = y;
        y = q;
    } while (q != 0);
    return res;
}

unsigned long long mult_mod(unsigned long long n, unsigned long long k, unsigned long long m) {
    unsigned long long acc, prod;
    if (k == 0)
        return 0;
    acc = n % m;
    prod = 0;
    for (; k > 0;) {
        if ((k % 2) == 1)
            prod = (prod + acc) % m;
        acc = (acc * 2) % m;
        k = k / 2;
    }
    return prod;
}

unsigned long long pow_mod(unsigned long long n, unsigned long long k, unsigned long long m) {
    unsigned long long mult = n % m;
    unsigned long long prod = 1;
    while (k > 0) {
        if ((k % 2) == 1) {
            prod = mult_mod(prod % m, mult % m, m);
            k = k - 1;
        }
        mult = mult_mod(mult % m, mult % m, m);
        k = k / 2;
    }
    return prod;
}

int test_ferma_prime(unsigned long long p) {
    unsigned long long a, pm, g;
    for (int i = 0; i < 100; ++i) {
        a = rand() % 1000;
        g = gcd(a, p);
        if (g == 1) {
            pm = pow_mod(a, p - 1, p);
            if (pm != 1)
                return 0;
        }
    }
    return 1;
}

void prime_init() {
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));

    srand(time(NULL));

    sv->n = SIEVE_ARR_SIZE_IN_BYTES;
    sv->mod1 = calloc(SIEVE_ARR_SIZE_IN_BYTES, sizeof(unsigned char));
    sv->mod5 = calloc(SIEVE_ARR_SIZE_IN_BYTES, sizeof(unsigned char));

    fill_sieve(sv);

    GLOBAL_SV = sv;
}

void prime_free() {
    free(GLOBAL_SV->mod1);
    free(GLOBAL_SV->mod5);
    free(GLOBAL_SV);
}

int is_prime(unsigned long long x) {
    unsigned long long max_sieve = SIEVE_ARR_SIZE_IN_BYTES * 8 * 6;
    if (x < max_sieve)
        return is_prime_sieve(GLOBAL_SV, x);
    return test_ferma_prime(x);
}

unsigned long long max_in_seq(unsigned k, unsigned n) {
    unsigned long long acc = 1, acc_prev = 0, tmp, result = 0;
    while (acc < (1ul << 60)) {
        tmp = acc;
        acc = k * acc + n * acc_prev;
        acc_prev = tmp;

        if (is_prime(acc_prev))
            result = acc_prev;
    }
    return result;
}

int main() {
    int res;
    unsigned k, n;

    res = scanf("%u%u", &k, &n);
    if (res != 2) {
        fprintf(stderr, "Input error\n");
        abort();
    }

    prime_init();

    printf("%lld\n", max_in_seq(k, n));

#ifdef TEST
    assert(max_in_seq(1, 1) == 99194853094755497);
    assert(max_in_seq(1, 2) == 768614336404564651);
    assert(max_in_seq(2, 1) == 1746860020068409);
    assert(max_in_seq(4, 4) == 0);
#endif

    prime_free();
}
