#include <stdio.h>
#include <assert.h>

long long iabs(long long x) { return (x < 0) ? -x : x; }

long long eu_mod(long long x, long long y) {
  long long r;
  assert(y != 0);
  r = x % y;
  if (r < 0) r += iabs(y);
  return r;
}

long long eu_div(long long x, long long y) {

  return (x - eu_mod(x, y)) / y;
}


int main() {
  long long x, y, a, a1, b, b1, r, q, c, d, t;
  long long check;
  int res;
  res = scanf("%lld%lld", &x, &y);
  assert(res == 2);

  a1 = b = 1;
  a = b1 = 0;
  c = x;
  d = y;
  
  while (1) {
    q = eu_div(c, d);
    r = eu_mod(c, d);
    check = d * q + r;
    printf("%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\n", a1, a, b1, b, c, d, q, r, check);
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
  printf("%lld %lld %lld\n", a, b, d);
  assert(d == a * x + b * y);
}
