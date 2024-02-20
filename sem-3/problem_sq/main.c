//
// Problem SQ — быстрая сортировка
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_arr(int const *arr, unsigned len);
void qsort_impl(int *arr, unsigned low, unsigned high);
void qsort_test(int *arr, unsigned len);

void swap(int *a, int *b);
unsigned partition(int *arr, unsigned low, unsigned high);

void print_arr(int const *arr, unsigned len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void qsort_impl(int *arr, unsigned low, unsigned high) {
  if (low >= high) return;
  unsigned pi = partition(arr, low, high);
  if (pi > low) qsort_impl(arr, low, pi - 1);
  qsort_impl(arr, pi + 1, high);
}

void qsort_test(int *arr, unsigned len) {
  qsort_impl(arr, 0u, len - 1);
}

void swap(int *a, int *b) {
  if (*a != *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
  }
}

unsigned partition(int *arr, unsigned low, unsigned high) {
  int *pivot = &arr[low];
  int l = low + 1, r = high;
  int lsf = 0, rsf = 0;

  while (l <= r) {
    if (!lsf && (arr[l] <= *pivot)) {
      l += 1;
    } else {
      lsf = 1;
    }
    if (!rsf && (arr[r] > *pivot)) {
      r -= 1;
    } else {
      rsf -= 1;
    }

    if (lsf && rsf) {
      if (l != r)
        swap(&arr[l], &arr[r]);
      lsf = 0;
      rsf = 0;
      l += 1;
      r -= 1;
    }
  }
  swap(pivot, &arr[l - 1]);
  return l - 1;
}

int main() {
  int arr[7] = {7, 6, 5, 4, 3, 2, 1};
  int len = 7;

  print_arr(arr, len);
  qsort_test(arr, len);
  print_arr(arr, len);
}