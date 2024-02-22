//
// Домашнее задание MPK — умножение гигантских полиномов, алгоритм Карацубы
//

#include <stdio.h>
#include <stdlib.h>

void print_arr(int const *arr, unsigned len);
void pmult_kar(int *p1, int *p2, int *res, int len);

void print_arr(int const *arr, unsigned len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void pmult_kar(int *p1, int *p2, int *res, int n) {
  if (n  == 1) {
    res[0] = p1[0] * p2[0];
  } else {
    // int k = n / 2;
    // (a1 + a2) -> aa; (b1 + b2) -> bb; (a1 + a2)*(b1 + b2) -> t
    // int aa[k], bb[k], t[n];
    // for (int i = 0; i < k; ++i) {
      
    // }

  }
}

int main() {
  int *p1, *p2, p1_len, p2_len;
  int *res, res_len;

  if (scanf("%u%u", &p1_len, &p2_len) != 2) {
    fprintf(stderr, "Input error\n");
    abort();
  }


  p1 = (int *)calloc(p1_len, sizeof(int));
  p2 = (int *)calloc(p2_len, sizeof(int));
  res_len = p1_len + p2_len - 1;
  res = (int *)calloc(res_len, sizeof(int));

  for (int i = 0; i < p1_len; ++i) {
    if (scanf("%d", &p1[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  for (int i = 0; i < p2_len; ++i) {
    if (scanf("%d", &p2[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  print_arr(p1, p1_len);
  print_arr(p2, p2_len);

  pmult_kar(p1, p2, res, res_len);

  print_arr(res, res_len);

  free(p1);
  free(p2);
}