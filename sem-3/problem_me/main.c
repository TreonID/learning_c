#include <stdio.h>
#include <stdlib.h>

void print_arr(const int *arr, unsigned len);
int majority_element(const int *parr, int len);

void print_arr(const int *arr, unsigned len) {
  unsigned i;
  for (i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

int majority_element(const int *parr, int len) {
  int i;
  int cnt = 0, candidate = parr[0], cnt_maj = 0;

  for (i = 1; i < len; ++i) {
    if (parr[i] == candidate) {
      cnt += 1;
      continue;
    }
    if (cnt == 0)
      candidate = parr[i];
    else
      cnt -= 1;
  }
  if (cnt == 0) return -1;

  for (i = 0; i < len; ++i)
    cnt_maj += (parr[i] == candidate) ? 1 : 0;

  if (cnt_maj > (len / 2))
    return candidate;
  return -1;
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

  print_arr(arr, len);
  printf("Majority element: %d\n", majority_element(arr, len));

  free(arr);
  return 0;
}