//
// Problem CSE — обобщённая сортировка выбором
//

#include <stdio.h>
#include <stdlib.h>

struct data_t {
  int *arr;
  unsigned len;
};

void print_data(const struct data_t data);
void swap(int *a, int *b);
void selectsort_iterate(int *arr, unsigned len, unsigned last);

typedef int (*cmp_t)(void const *lhs, void const *rhs);
int selstep(void *parr, int eltsize, int numelts, int nsorted, cmp_t cmp);

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

int min_pos(int *arr, unsigned len) {
  int min = arr[0], pos = 0;
  for (int i = 0; i < len; ++i) {
    if (arr[i] < min) {
      min = arr[i];
      pos = i;
    }
  }
  return pos;
}

void selectsort_iterate(int *arr, unsigned len, unsigned last) {
  int pos = last + min_pos(arr + last, len - last);
  swap(&arr[pos], &arr[last]);
}

int cmin_pos(void *arr, int eltsize, int numelts, cmp_t cmp) {
  char *min = (char *)arr;
  char *ppos;
  int pos = 0;
  for (int i = 0; i < numelts; ++i) {
    ppos = arr + (i * eltsize);
    if (cmp(ppos, min)) {
      min = ppos;
      pos = i;
    }
  }
  return pos;
}

void copy(void *from_a, void *to_b, int eltsize) {
  char *c_from = (char *)from_a;
  char *c_to = (char *)to_b;
  for (int i = 0; i < eltsize; ++i) {
    c_to[i] = c_from[i];
  }
}

void cswap(void *parr, int pad_a, int pad_b, int eltsize) {
  char *cparr = (char *)parr;
  char *tmp = (char *)calloc(eltsize, sizeof(char));
  char *cpa = cparr + pad_a * eltsize;
  char *cpb = cparr + pad_b * eltsize;
  if (pad_a == pad_b)
    return;
  copy(cpa, tmp, eltsize);
  copy(cpb, cpa, eltsize);
  copy(tmp, cpb, eltsize);

  free(tmp);
}

int selstep(void *parr, int eltsize, int numelts, int nsorted, cmp_t cmp) {
  int pos = nsorted + cmin_pos((char *)parr + (nsorted * eltsize), eltsize, numelts - nsorted, cmp);
  cswap(parr, pos, nsorted, eltsize);
  return 0;
}

int intless(void const *lhs, void const *rhs) {
  int const *ilhs = (int *)lhs;
  int const *irhs = (int *)rhs;
  if (*ilhs < *irhs)
    return 1;
  return 0;
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

  print_data(d);
  selstep(d.arr, sizeof(int), d.len, last, intless);
  print_data(d);

  free(d.arr);
}