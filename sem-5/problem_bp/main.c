/* Problem BP — упаковка рюкзака */

#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int read_int() {
  int tmp;
  if (scanf("%d", &tmp) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  return tmp;
}

void fill_value(int *arr, int value, size_t size) {
  for (size_t i = 0; i < size; ++i)
    arr[i] = value;
}

int min(int a, int b) {
  return (a > b) ? b : a;
}

int max(int a, int b) {
  return (a > b) ? b : a;
}

int main() {
  int m, n;
  int *changes, *V;
  int res;

  n = read_int();
  m = read_int();

  changes = calloc(m, sizeof(int));
  for (int i = 0; i < m; ++i)
    changes[i] = read_int();

  V = calloc(n + 1, sizeof(int));
  fill_value(V, INT_MAX, n + 1);

  res = calc_change(n, m, changes, V);
  printf("%d\n", res);

  free(V);
  free(changes);
}