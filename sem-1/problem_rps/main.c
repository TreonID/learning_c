#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned pow_mod(unsigned n, unsigned k, unsigned m) {
  unsigned mult = n % m;
  unsigned prod = 1;
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

unsigned spow_mod(unsigned a, unsigned b, unsigned n) {
  unsigned mult = a % n;
  unsigned prod = 1;
  if (b == 1) {
    return mult;
  }
  b++;
  while(b > 0) {
    if ((b % 2) == 1) {
      prod = pow_mod(mult, prod, n);
      b = b - 1;
    }
    mult = pow_mod(mult, a, n);
    b = b / 2;
  }
  return prod;
}

int main() {
  unsigned a, b, n;
  int res;

  res = scanf("%u%u%u", &a, &b, &n);
  if (res != 3) {
    fprintf(stderr, "Input error");
    abort();
  }

  printf("%u\n", spow_mod(a, b, n));
}

