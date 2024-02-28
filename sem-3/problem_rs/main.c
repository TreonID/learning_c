#include <stdio.h>
#include <stdlib.h>

void print_arr(const int *arr, unsigned len);

void print_arr(const int *arr, unsigned len) {
  unsigned i;
  for (i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void radix_sort(int *parr, int len, int r_pos) {
  int i, expn = 1;
  int b[10] = {0};
  int *res = calloc(len, sizeof(int));

  for (i = 0; i < r_pos; ++i)
    expn *= 10;

  for (i = 0; i < len; ++i)
    b[(parr[i] / expn) % 10] += 1;
  for (i = 1; i < 10; ++i)
    b[i] += b[i - 1];

  for (i = len - 1; i >= 0; i--) {
    res[b[(parr[i] / expn) % 10] - 1] = parr[i];
    b[(parr[i] / expn) % 10]--;
  }

  for (i = 0; i < len; ++i)
    parr[i] = res[i];
  free(res);
}

int main() {
  int *arr, len, i, r_pos;

  if (scanf("%d", &len) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  arr = (int *)calloc(len, sizeof(int));

  for (i = 0; i < len; ++i) {
    if (scanf("%d", &arr[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  if (scanf("%d", &r_pos) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  radix_sort(arr, len, r_pos);
  print_arr(arr, len);

  free(arr);
  return 0;
}