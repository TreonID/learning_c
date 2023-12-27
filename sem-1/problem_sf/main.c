#include <stdio.h>
#include <stdlib.h>

#define MAX_FIB 40

int fibs[MAX_FIB] = {0, 1, 1};

int fib(int x) {
  int first = 0, second = 1, tmp, id;
  if (x == 0) return 0;
  if (x < MAX_FIB && fibs[x] != 0) return fibs[x];
  for (id = 2; id <= x; ++id) {
    tmp = second;
    second = second + first;
    first = tmp;
  }
  if (x < MAX_FIB && fibs[x] == 0) fibs[x] = second;
  return second;
}

void print_sf(int x) {
  int i = 1, max_fib = 0, max_i, rest;
  if (x == 0) printf("0\n");
  if (x == 1) printf("1\n");
  if (x == 2) printf("10\n");
  if (x < 3) return;

  while (max_fib < x) {
    ++i;
    max_fib = fib(i);
  }
  max_i = i-1;

  rest = x;
  for (i = max_i; i > 1; --i) {
    printf("%d", (rest / fib(i) == 1) ? 1: 0); 
    rest = rest % fib(i);
  }
  printf("\n");
}

int main() {
  int x, res;
  res = scanf("%d", &x);
  if (res != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  
  print_sf(x);

}
