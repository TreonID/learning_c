//
// Problem MS — слияние для сортировки слиянием
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_arr(int const *arr, unsigned len);

void merge_sort_imp(int *arr, int l, int r);
void merge_sort(int *arr, int n);
void merge(int *arr, int l, int m, int r);

void print_arr(int const *arr, unsigned len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void merge_sort_imp(int *arr, int l, int r) {
  if (l >= r) return;
  int m = (l + r) / 2;
  merge_sort_imp(arr, l, m);
  merge_sort_imp(arr, m + 1, r);
  merge(arr, l, m, r);
}

void merge_sort(int *arr, int n) {
  merge_sort_imp(arr, 0, n - 1);
}

void merge(int *arr, int l, int m, int r) {
  int len = 1 + r - l;
  int *tmp = calloc(len, sizeof(int));
  int k = 0;

  int *p1 = &arr[l], *p2 = &arr[m + 1];
  int *p1_max = &arr[m], *p2_max = &arr[r];

  while (p1 <= p1_max && p2 <= p2_max) {
    if (*p1 < *p2) {
      tmp[k] = *p1;
      p1 += 1;
      k += 1;
    } else {
      tmp[k] = *p2;
      p2 += 1;
      k += 1;
    }
  }

  if (p1 <= p1_max) {
    while (p1 <= p1_max) {
      tmp[k] = *p1;
      k += 1;
      p1 += 1;
    }
  }

  if (p2 <= p2_max) {
    while (p2 <= p2_max) {
      tmp[k] = *p2;
      k += 1;
      p2 += 1;
    }
  }

  for (int i = 0; i < len; ++i) {
    arr[l + i] = tmp[i];
  }
  free(tmp);
}

int main() {
  int *arr, len;

  if (scanf("%u", &len) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  arr = (int *)malloc(len * sizeof(int));

  for (int i = 0; i < len; ++i) {
    if (scanf("%d", &arr[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  merge_sort(arr, len);
  print_arr(arr, len);

  free(arr);
}