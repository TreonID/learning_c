#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};

int is_prime(struct sieve_t *sv, unsigned n);

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

void fill_sieve(struct sieve_t *sv) {
    int bound = (sv->n * 8) * 6 + 5;
    set_bit(sv->mod1, 0);
    for (int i = 2; i * i <= bound; ++i) {
        if (is_prime(sv, i))
            for (int j = 2; i * j <= bound; ++j) {
                if ((i * j - 1) % 6 == 0)
                    set_bit(sv->mod1, (i * j) / 6);
                else if ((i * j - 5) % 6 == 0)
                    set_bit(sv->mod5, (i * j) / 6);
            }
    }
}

int is_prime(struct sieve_t *sv, unsigned n) {
    int max_size = (sv->n * 8) * 6 + 5;
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

int n_count_prime(struct sieve_t *sv, int n) {
    int max_size = (sv->n * 8) * 6 + 5;
    int count = 0;

    for (int i = 1; i < max_size; ++i) {
        if (is_prime(sv, i)) ++count;
        if (count == n) return i;
    }

    return -1;
}

struct sieve_t *sieve_init(long long bound) {
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));
    sv->n = bound;
    sv->mod1 = calloc(bound, sizeof(unsigned char));
    sv->mod5 = calloc(bound, sizeof(unsigned char));
    fill_sieve(sv);
    return sv;
}

void sieve_free(struct sieve_t *sv) {
    free(sv->mod1);
    free(sv->mod5);
    free(sv);
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

unsigned long long pow_mod(unsigned long long n, unsigned long long k, unsigned long long m) {
    unsigned long long mult = n % m;
    unsigned long long prod = 1;
    while (k > 0) {
        if ((k % 2) == 1) {
            prod = (prod * mult) % m;
            k = k - 1;
        }
        mult = (mult * mult) % m;
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

int main() {

    srand(time(NULL));

    printf("%lld\n", gcd(984, 413958827741)); 
    printf("%lld\n", pow_mod(984, 413958827741-1, 413958827741)); 

#ifdef TEST
    printf("%d\n", test_ferma_prime(413958827741));

    assert(test_ferma_prime(100000001) == 0);
    assert(test_ferma_prime(100000007) == 1);
    assert(test_ferma_prime(413958827669) == 0);
    assert(test_ferma_prime(413958827741) == 1);
    assert(test_ferma_prime(5394826801) == 1);
#endif
}
