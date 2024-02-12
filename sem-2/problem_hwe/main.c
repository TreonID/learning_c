#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};

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
    set_bit(sv->mod1, 0);
    for (int i = 2; i * i <= (sv->n * 8) * 6 + 5; ++i)
        if ((get_bit(sv->mod1, i * 6 + 1) == 0u) && (get_bit(sv->mod5, i * 6 + 5) == 0u)) {
            for (int j = 2; i * j <= (sv->n * 8) * 6 + 5; ++j) {
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
    for (int i = 1; i < max_size;++i) {
        if (is_prime(sv, i)) ++count;
        if (count == n) return i; 
    }
    return -1;
}

int main() {
    // For test
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));
    int bound = 1000;

    sv->n = bound;
    sv->mod1 = calloc(bound, sizeof(unsigned char));
    sv->mod5 = calloc(bound, sizeof(unsigned char));

    fill_sieve(sv);

    printf("Test 1 10: %d\n", n_count_prime(sv, 10));
    printf("Test 2 20: %d\n", n_count_prime(sv, 20));
    printf("Test 3 50: %d\n", n_count_prime(sv, 50));
    

    free(sv->mod1);
    free(sv->mod5);
    free(sv);
}
