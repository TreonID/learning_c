#include <stdio.h>
#include <stdlib.h>

unsigned pisanos[1000] = {0, 1};

unsigned get_pisano_period(unsigned m) {
  int first = 0, second = 1, tmp, period = 0;
  if (m == 0) return 0;
  if (m < 1000 && pisanos[m] != 0) return pisanos[m]; 
  for (; ; ) {
    tmp = second;
    second = (second + first) % m;
    first = tmp;
    period++;
    if (first == 0 && second == 1) {
      if (m < 1000) pisanos[m] = period;
      return period;
    }
  }
}

unsigned fib_mod(unsigned long long x, unsigned m) {
  unsigned first = 0, second = 1, tmp, id;
  
  x = x % get_pisano_period(m);
  
  if (x == 0) return 0;
  if (x < 3) return 1;
  for (id = 2; id <= x; ++id) {
    tmp = second;
    second = (second + first) % m;
    first = tmp;
  }
  return second;
}

int main() {
  unsigned long long x;
  unsigned m;
  int res;
  res = scanf("%llu%u", &x, &m);
  if (res != 2) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  printf("%u %u\n", fib_mod(x, m), get_pisano_period(m));

}
