/* Problem EX — работа с битами плавающих чисел */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

unsigned as_uint(float f) {
  unsigned u;
  memcpy(&u, &f, sizeof(unsigned));
  return u;
}

float as_float(unsigned u) {
  float f;
  memcpy(&f, &u, sizeof(float));
  return f;
}

int main() {
  float f;
  unsigned u, m = 0x2aaaaa; // 001010101010101010101010

  if (scanf("%f", &f) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  u = as_uint(f) ^ m;
  f = as_float(u);
  
  printf("%.5f\n", f);
}