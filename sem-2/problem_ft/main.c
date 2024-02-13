#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    unsigned long long m1, m2, m3, m4;
    while (k > 0) {
        if ((k % 2) == 1) {
            m1 = prod % m;
            m2 = mult % m;
            //            prod = (m1 * m2) % m;
            prod = mult_mod(m1, m2, m);
            k = k - 1;
        }
        m3 = mult % m;
        m4 = mult % m;
        // mult = (m3 * m4) % m;
        mult = mult_mod(m3, m4, m);
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
    int res;
    unsigned long long p;

    res = scanf("%lld", &p);
    if (res != 1) {
        fprintf(stderr, "Input error\n");
        abort();
    }

    srand(time(NULL));
    printf("%d\n", test_ferma_prime(p));

#ifdef TEST
    assert(test_ferma_prime(100000001) == 0);
    assert(test_ferma_prime(100000007) == 1);
    assert(test_ferma_prime(413958827669) == 0);
    assert(test_ferma_prime(413958827741) == 1);
    assert(test_ferma_prime(5394826801) == 1);
#endif
}
