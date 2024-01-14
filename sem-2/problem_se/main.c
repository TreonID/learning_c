#include <stdio.h>
#include <stdlib.h>

int main() {
  int res, n, sum = 0;
  char *sieve;

  res = scanf("%d", &n);
  if (res != 1 || n <= 0) {
    fprintf(stderr, "Input error, n > 0\n");
  }

  sieve = calloc(n + 1, sizeof(char));
  for (int i = 2; i * i <= n; ++i) {
    for (int j = 2; i * j <= n; ++j) {
      sieve[i * j] = 1;
    }
  }
  
  for (int i = 2; i <= n; ++i)
    if (sieve[i] == 0) sum += 1;

  printf("%d\n", sum);
  
  free(sieve);

}

