/* Problem RP — верхняя и нижняя границы */

#include <fenv.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

unsigned as_uint(float f) {
  unsigned u;
  memcpy(&u, &f, sizeof(unsigned));
  return u;
}

unsigned get_exp(float f) {
  unsigned u = as_uint(f);
  u <<= 1;
  u >>= 24;
  return u;
}

unsigned get_frac(float f) {
  unsigned u = as_uint(f);
  u <<= 9;
  u >>= 9;
  return u;
}

float as_float(unsigned u) {
  float f;
  memcpy(&f, &u, sizeof(float));
  return f;
}

int main() {
  int num, den;
  float f1, f2;
  unsigned e1, e2, fr1, fr2;
  if (scanf("%d", &num) != 1) {
    fprintf(stderr, "Input error: numerator\n");
    abort();
  }
  if (scanf("%d", &den) != 1) {
    fprintf(stderr, "Input error: denominator\n");
    abort();
  }

  fesetround(FE_TOWARDZERO);
  f2 = roundf((float)num) / (float)den;
  fesetround(FE_DOWNWARD);
  f1 = (float)num / (float)den;

  e1 = get_exp(f1);
  e2 = get_exp(f2);
  fr1 = get_frac(f1);
  fr2 = get_frac(f2);
  
  if ((e1 == e2) && (fr1 == fr2)) {
    printf("0x%x 0x%x\n", get_exp(f2), get_frac(f2));
  } else {
    printf("0x%x 0x%x ", get_exp(f1), get_frac(f1));
    printf("0x%x 0x%x\n", get_exp(f2), get_frac(f2));
  }
}