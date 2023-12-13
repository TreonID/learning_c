#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
  int n = nod(a, b), x, y, x1 = 0;
  if (eu_mod(c, n) != 0) {
    printf("NONE\n");
    return ;
  }
  x = b * x1;
  y = eu_div(c, b) - a * x1;
  printf("%d %d\n", x, y);
  assert(a * x + b * y == c);
}


void print_ee(int x, int y) {
  int a, a1, b, b1, r, q, c, d, t;
  a1 = b = 1;
  a = b1 = 0;
  c = x;
  d = y;

  for (; ; ) {
    q = eu_div(c, d);
    r = eu_mod(c, d);
#if 0
    printf("%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\n", a1, a, b1, b, c, d, q, r, check);
#endif
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
  printf("%d %d %d\n", a, b, d);
}





int main() {
  int a, b, c, res;
  
  res = scanf("%d%d%d", &a, &b, &c);
  if (res != 3) {
    fprintf(stderr, "Input error");
    abort();
  }

  printf("%d*x + %d*y = %d\n", a, b, c);
#if 0
  print_de(a, b, c);
#endif
  printf("NOD(%d,%d) = %d\n", a, b, nod(a, b));
  print_ee(a, b);
}
