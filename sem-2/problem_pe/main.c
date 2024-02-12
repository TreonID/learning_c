#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
    int n;
    unsigned char *s;
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
    set_bit(sv->s, 0);
    set_bit(sv->s, 1);
    for (int i = 2; i * i <= (sv->n * 8); ++i)
        if (get_bit(sv->s, i) == 0u)
            for (int j = 2; i * j <= (sv->n * 8); ++j)
                set_bit(sv->s, i * j);
}

int is_prime(struct sieve_t *sv, unsigned n) {
    int max_bytes = (n / 8) + ((n % 8) ? 1 : 0);
    if (max_bytes > sv->n) {
        printf("Error: out of bounds, %d\n", n);
        return 0;
    }
    return (get_bit(sv->s, n) == 1u) ? 0 : 1;
}

int main() {
    // For test
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));
    int bound = 10;

    sv->n = bound;
    sv->s = calloc(bound, sizeof(char));
    fill_sieve(sv);
    printf("%x\n", is_prime(sv, 81));

    assert(get_bit(sv->s, 2) == 0u);
    assert(get_bit(sv->s, 3) == 0u);
    assert(get_bit(sv->s, 4) == 1u);
    assert(get_bit(sv->s, 5) == 0u);
    assert(get_bit(sv->s, 6) == 1u);
    assert(get_bit(sv->s, 7) == 0u);
    assert(get_bit(sv->s, 8) == 1u);
    assert(get_bit(sv->s, 9) == 1u);
    assert(get_bit(sv->s, 10) == 1u);
    assert(get_bit(sv->s, 11) == 0u);

    free(sv->s);
    free(sv);
}
