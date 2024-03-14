/* Problem MC — размен монет */

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

int calc_change(int n, int m, int *changes, int *V) {
  int i;
  if (n == 0) return 0;
  if (n < 0) return INT_MAX;
  if (V[n] != INT_MAX) return V[n];
  for (i = 0; i < m; ++i) {
    int CT = calc_change(n - changes[i], m, changes, V);
    if (CT == INT_MAX) continue;
    V[n] = min(V[n], CT + 1);
  }
  return V[n];
}

int main() {
  int m, n;
  int *changes, *V;

  n = read_int();
  m = read_int();

  changes = calloc(m, sizeof(int));
  for (int i = 0; i < m; ++i)
    changes[i] = read_int();

  V = calloc(n + 1, sizeof(int));
  fill_value(V, INT_MAX, n + 1);

  printf("%d\n", calc_change(n, m, changes, V));

  free(V);
  free(changes);
}