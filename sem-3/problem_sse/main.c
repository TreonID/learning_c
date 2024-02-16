#include <stdio.h>
#include <stdlib.h>

struct data_t {
  int *arr;
  unsigned len;
};

void print_data(const struct data_t data);
void swap(int *a, int *b);
void selectsort_iterate(int *arr, unsigned len, unsigned last);

void print_data(const struct data_t data) {
  for (int i = 0; i < data.len; ++i) {
    printf("%d", data.arr[i]);
    if (i != data.len - 1) printf(" ");
  }
  printf("\n");
}

void swap(int *a, int *b) {
  if (*a != *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
  }
}

void selectsort_iterate(int *arr, unsigned len, unsigned last) {
  int min = arr[last], pos = last;
  for (int i = last; i < len; ++i)
    if (arr[i] < min) {
      min = arr[i];
      pos = i;
    }
  swap(&arr[pos], &arr[last]);
}

int main() {
  int i, last;
  struct data_t d;

  if (scanf("%u", &d.len) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  if (d.len == 0) {
    printf("0\n");
    return 0;
  }

  d.arr = (int *)malloc(d.len * sizeof(int));

  if (d.arr == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }

  for (i = 0; i < d.len; ++i) {
    if (scanf("%d", &d.arr[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  if (d.len == 1) {
    printf("%d\n", d.arr[0]);
    return 0;
  }

  if (scanf("%d", &last) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  selectsort_iterate(d.arr, d.len, last);
  print_data(d);

  free(d.arr);
}