#include <math.h>
#include <fenv.h>
#include <memory.h>
#include <stdio.h>

unsigned as_uint(float f) {
  unsigned u;
  memcpy(&u, &f, sizeof(unsigned));
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
    float num = -1.0f, den = 3.0f;
    float f;
    unsigned tar = 0xbeaaaaac; // -0.33333337306976318359375000

    printf("0x%x\n", get_frac(as_float(tar)));
    printf("%.40f\n", as_float(tar));

    f = num / den;
    printf("0x%x\n", get_frac(f));
    printf("%.40f\n", f);
    

    fesetround(FE_UPWARD);
    f = num / den;
    printf("0x%x\n", get_frac(f));
    printf("%.40f\n", f);

    fesetround(FE_DOWNWARD);
    f = num / den;
    printf("0x%x\n", get_frac(f));
    printf("%.40f\n", f);

    fesetround(FE_TONEAREST);
    f = num / den;
    printf("0x%x\n", get_frac(f));
    printf("%.40f\n", f);

    fesetround(FE_TOWARDZERO);
    f = num / den;
    printf("0x%x\n", get_frac(f));
    printf("%.40f\n", f);
}