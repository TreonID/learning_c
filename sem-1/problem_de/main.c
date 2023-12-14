#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct res_ee_t {
  int a, b, c;
};

struct res_ee_t *calc_ee(int x, int y);

int iabs(int x) { return (x < 0) ? -x : x; }

int eu_mod(int x, int y) {
  int r;
  assert(y != 0);
  r = x % y;
  if (r < 0) r += iabs(y);
  return r;
}

int eu_div(int x, int y) { 
  assert(y != 0);
  return (x - eu_mod(x, y)) / y; 
}


int nod(int m, int n) {
  int r = 0;
  for (; ; ) {
    r = eu_mod(m, n);
    if (r == 0) {
      break;
    }
    m = n;
    n = r;
  };
  return n;  
}

void print_de(int a, int b, int c) {
  struct res_ee_t *ee = calc_ee(a, b);
  int n = nod(a, b), x, y, d_mult;
  if (eu_mod(c, n) != 0) {
    printf("NONE\n");
    return ;
  }
  
//  d_mult = ee->c * c / iabs(ee->c);
  d_mult = (ee->c < 0) ? -c: c;
  x = ee->a * d_mult;
  y = ee->b * d_mult;
  printf("%d %d\n", x, y);
  assert(a * x + b * y == c);
  free(ee);
}


struct res_ee_t *calc_ee(int x, int y) {
  struct res_ee_t *result;
  int a, a1, b, b1, r, q, c, d, t;
  a1 = b = 1;
  a = b1 = 0;
  c = x;
  d = y;

  for (; ; ) {
    q = eu_div(c, d);
    r = eu_mod(c, d);
    if (r == 0) break;

    c = d;
    d = r;
    t = a1;
    a1 = a;
    a = t - (q * a);
    t = b1;
    b1 = b;
    b = t - (q * b);

  }
  
  result = calloc(1, sizeof(struct res_ee_t));
  result->a = a;
  result->b = b;
  result->c = d;

#if 0
  printf("EE: %d %d %d\n", a, b, d);
#endif
  return result;
}


int main() {
  int a, b, c, res;
  
  res = scanf("%d%d%d", &a, &b, &c);
  if (res != 3) {
    fprintf(stderr, "Input error");
    abort();
  }
  print_de(a, b, c);
}
