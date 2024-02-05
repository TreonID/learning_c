#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct sieve_t {
  int n;
  char *s;
};

void fill_sieve(struct sieve_t *sv) {
  for (int i = 2; i * i <= sv->n; ++i) {
    if (sv->s[i] == 0)
        for (int j = 2; i * j <= sv->n; ++j) {
        sv->s[i * j] = 1;
        }
  }
}

int is_prime(struct sieve_t sv, int x) {
  return (sv.s[x] == 1) ? 0 : 1; 
}

int nth_prime(struct sieve_t *sv, int N) {
    int j = 0;
    for (int i = 2; i <= sv->n; ++i) 
        if (is_prime(*sv, i)) {

            ++j;
            if (j == N) return i;
        }
    return -1;
}

long long sieve_bound(int num) {
    if (num <= 20) return 100;
    double dnum = num;
    double dres = dnum * (log(dnum) + log(log(dnum)));
    return (long long) round(dres);
}

int main() {
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));
    int n = 10000000;
    long long bound = sieve_bound(n);
    sv->n = bound;
    sv->s = calloc(bound, sizeof(char));
    fill_sieve(sv);
    printf("Sieve is filled!\n");
    printf("%d\n", nth_prime(sv, n));
    free(sv);
}