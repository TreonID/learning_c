//
// Problem SCB — обобщённый бинарный поиск
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_t)(void const *lhs, void const *rhs);

void print_arr(int const *arr, unsigned len);
unsigned binary_search_int(int const *parr, unsigned len, int elem);

int int_cmp(void const *lhs, void const *rhs);
void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp);

void print_arr(int const *arr, unsigned len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

unsigned binary_search_int(int const *parr, unsigned len, int elem) {
  int l = 0;
  int r = len - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (parr[m] == elem) return m;
    if (parr[m] < elem) l = m + 1;
    if (parr[m] > elem) r = m - 1;
  }
  return len;
}

int int_cmp(void const *lhs, void const *rhs) {
  int const *ilhs = (int *)lhs;
  int const *irhs = (int *)rhs;
  return *ilhs - *irhs;
}

void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp) {
  int l = 0;
  int r = num - 1;
  char const *cbase = (char const *)base;

  while (l <= r) {
    int m = l + (r - l) / 2;
    char const *pad_cbase = cbase + m * size;
    if (cmp(pad_cbase, key) == 0)
      return (void *)pad_cbase;
    if (cmp(pad_cbase, key) < 0)
      l = m + 1;
    if (cmp(pad_cbase, key) > 0)
      r = m - 1;
  }
  return NULL;
}

int main() {
  int arr[6] = {1, 12, 12, 14, 23, 57};
  int len = 6;

  int needle = 23;
  printf("RES=%p\n", arr);
  printf("RES=%p\n", cbsearch(&needle, arr, len, sizeof(int), int_cmp));
  printf("DELTA=%ld\n", (cbsearch(&needle, arr, len, sizeof(int), int_cmp) - (void *)arr) / sizeof(int));
}