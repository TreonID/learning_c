#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

unsigned fact(unsigned x) {
  if (x == 0) return 1;
  if (x == 1) return 1;
  return x * fact(x - 1);
}

void fact_system(unsigned x) {
	unsigned k, i, p, factor;
  int max_factor_i = -1;

  if (x == 0) {
    printf("0.\n");
    return;
  }

  for (int i = 1; i < 13; ++i) {
    if (fact(i) > x) {
      max_factor_i = i-1;
      break;
    }
    if (fact(i) == x) {
      max_factor_i = i;
      break;
    }
  }
  assert(max_factor_i != -1);

  i = max_factor_i;
  p = 0;
  for (i = max_factor_i; i > 0; --i) {
    factor = fact(i);
    k = x / factor;
    x = x % factor;
    printf("%u.", k);
    p++;
  }
  printf("\n");
}


int main() {
  int res;
	unsigned x;
	res = scanf("%u", &x);
  if (res != 1) {
    fprintf(stderr, "Input error");
    abort();
  }
	fact_system(x);
}
