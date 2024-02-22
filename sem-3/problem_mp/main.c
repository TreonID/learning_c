//
// Problem MP — умножение полиномов
//

#include <stdio.h>
#include <stdlib.h>

void print_arr(int const *arr, unsigned len);
void print_polymult(int *p1, unsigned p1_len, int *p2, unsigned p2_len);

void print_arr(int const *arr, unsigned len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void print_polymult(int *p1, unsigned p1_len, int *p2, unsigned p2_len) {
  int i, j, n = p1_len - 1, m = p2_len - 1;
  int res_len = n + m + 1;
  int *res = calloc(res_len, sizeof(int));
  int pad = 0;

  for (i = 0; i <= n; ++i)
    if (p1[i] != 0)
      for (j = 0; j <= m; ++j)
        if (p2[j] != 0)
          res[i + j] += p1[i] * p2[j];

  for (i = res_len - 1; i >= 0; --i)
    if (res[i] == 0)
      pad += 1;
    else
      break;

  print_arr(res, res_len - pad);

  free(res);
}

int main() {
  int *p1, *p2, p1_len, p2_len;

  if (scanf("%u%u", &p1_len, &p2_len) != 2) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  p1 = (int *)calloc(p1_len, sizeof(int));
  p2 = (int *)calloc(p2_len, sizeof(int));

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

  print_polymult(p1, p1_len, p2, p2_len);

  free(p1);
  free(p2);
}