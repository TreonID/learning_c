#include <stdio.h>
#include <stdlib.h>

unsigned fib(unsigned x, unsigned m) {
  unsigned first = 0u, second = 1u, id, tmp;
  if (x == 0) return 0u;
  
  for (id = 2; id <= x; ++id) {
    tmp = second;
    second = (second + first) % m;
    first = tmp;
  }
  return second;
}

int main() {
  unsigned x, m, res;
  res = scanf("%u%u", &x, &m);
  if (res != 2) {
    fprintf(stderr, "Input error");
    abort();
  }

  printf("%u\n", fib(x, m)); 
  
}
