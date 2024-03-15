/* Problem BP — упаковка рюкзака */

#include <assert.h>
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
  return (a > b) ? a : b;
}

int max3(int a, int b, int c) {
  return max(max(a, b), c);
}

void print_table(int **V, int *stuffs, int s_count, int w) {
  printf("i\tWi\\W\t");
  for (int j = 0; j < w + 1; ++j) {
    printf("%d\t", j);
  }
  printf("\n");
  for (int i = 0; i < s_count + 1; ++i) {
    for (int j = 0; j < w + 1; ++j) {
      if (j == 0)
        printf("%d\t%d\t", i, stuffs[i]);

      printf("%d\t", V[i][j]);
    }
    printf("\n");
  }
}

void build_table(int **V, int *stuffs, int s_count, int w) {
  for (int i = 1; i <= s_count; ++i)
    for (int c = 1; c <= w; ++c) {
      V[i][c] = V[i - 1][c];

      if ((c / stuffs[i]) > 0)
        V[i][c] = max(V[i][c], V[i - 1][c - stuffs[i]] + 1);
    }

}

int int_comp(const void *a, const void *b) {
  const int *pa = a;
  const int *pb = b;
  return *pa - *pb;
}

int main() {
  int w, s_count;
  int *stuffs, **V;
  int res;

  w = read_int();
  s_count = read_int();

  stuffs = calloc(s_count + 1, sizeof(int));
  for (int i = 1; i < s_count + 1; ++i)
    stuffs[i] = read_int();

  V = calloc(s_count + 1, sizeof(int *));
  for (int i = 0; i < s_count + 1; i++) {
    V[i] = calloc(w + 1, sizeof(int));
  }

  qsort(stuffs, s_count + 1, sizeof(int), int_comp);

  build_table(V, stuffs, s_count, w);
  res = V[s_count][w];
#if 0
  print_table(V, stuffs, s_count, w);
#endif
  printf("%d\n", res);

  for (int i = 0; i < s_count + 1; i++)
    free(V[i]);
  free(V);
  free(stuffs);
}