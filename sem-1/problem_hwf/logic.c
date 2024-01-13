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

int next_turn(int total, int possible) {
  int i = 1, max_fib = 0, max_i, rest, last_i;
  while (max_fib <= total) {
    ++i;
    max_fib = fib(i);
  }
  max_i = last_i = i - 1; 

  rest = total;
  for (i = max_i; i > 1; --i) {
    if (rest / fib(i) == 1) {
      last_i = i;
    }
    rest = rest % fib(i);
  }
  
  return (fib(last_i) <= possible) ? fib(last_i) : 1;
}

