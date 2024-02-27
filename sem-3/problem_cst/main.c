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

int max(int *parr, int len) {
  int max = parr[0];
  if (len == 1) return max;
  for (int i = 1; i < len; ++i) {
    if (parr[i] > max)
      max = parr[i];
  }
  return max;
}

void print_buckets(int *parr, int len) {
  int b_count = max(parr, len) + 1;
  int *buckets = calloc(b_count, sizeof(int));

  for (int i = 0; i < len; ++i) {
    buckets[parr[i]] += 1;
  }

  print_arr(buckets, b_count);

  free(buckets);
}

int main() {
  int *arr, len, i;

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

  print_buckets(arr, len);

  free(arr);
  return 0;
}