#include <stdio.h>
#include <stdlib.h>

#include "logic.h"

#define MAX_FIB 40

int main() {
  int x, res;
  res = scanf("%d", &x);
  if (res != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  
  printf("%d\n", next_turn(x, 2));

}
