#include <stdio.h>
#include <stdlib.h>

int main() {
  int res, a, b, q, r;
  res = scanf("%d%d", &a, &b);
  if (res != 2) abort();

  for (;;) {
    q = a / b;
    r = a % b;
    printf("%d ", q);
    a = b;
    b = r;
    if (r == 0) break;
  }
  printf("\n");
}
