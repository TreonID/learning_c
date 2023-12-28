#include <stdio.h>
#include <stdlib.h>


void matrix_mult22_mod(unsigned *m1, unsigned *m2, unsigned *result, unsigned m);

void pow_matrix22(unsigned *n, unsigned k, unsigned m, unsigned *res) {
  int i;
  unsigned mult[4];
  unsigned prod[4] = {1, 0, 0, 1};

  for (i = 0; i < 4; ++i) {
    mult[i] = n[i] % m;
  }

  while (k > 0) {
    if ((k % 2) == 1) {
      matrix_mult22_mod(prod, mult, prod, m);
      k = k - 1;
    }
    matrix_mult22_mod(mult, mult, mult, m);
    k = k / 2;
  }

  for (i = 0; i < 4; ++i) {
    res[i] = prod[i];
  }
}

void matrix_mult22_mod(unsigned *m1, unsigned *m2, unsigned *output, unsigned m) {
  unsigned result[4] = {0};
  int i;
  result[0] = (m1[0] * m2[0] + m1[1] * m2[2]) % m;
  result[1] = (m1[0] * m2[1] + m1[1] * m2[3]) % m;
  result[2] = (m1[2] * m2[0] + m1[3] * m2[2]) % m; 
  result[3] = (m1[2] * m2[1] + m1[3] * m2[3]) % m;
  for (i = 0; i < 4; ++i) {
    output[i] = result[i];
  }
}

void print_matrix22(unsigned *m) {
  printf("%u %u ", m[0], m[1]);
  printf("%u %u\n", m[2], m[3]);
}

int main() {
  unsigned x[4], mult[4], m, n;
  int res, i;
  for (i = 0; i < 4; ++i) {
    res = scanf("%u", &x[i]);
    if (res != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }
  res = scanf("%u%u", &n, &m); 
  if (res != 2) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  
  pow_matrix22(x, n, m, mult);
  print_matrix22(mult);
 
}
