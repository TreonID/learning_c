#include <stdio.h>
#include <stdlib.h>

void print_arr(int const *arr, unsigned len);

void print_arr(int const *arr, unsigned len) {
  unsigned i;
  for (i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void p_mult(int *a, int *b, int *c, int n) {
  if (n == 1) {
    c[0] += a[0] * b[0];
  } else {
    int k = n / 2;
    p_mult(a, b, c, k);
    p_mult(a + k, b + k, c + n, k);
    p_mult(a + k, b, c + k, k);
    p_mult(a, b + k, c + k, k);
  }
}

void p_mult_kar(int *a, int *b, int *c, int n) {
  int i, j;
  if (n <= 64) {
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        c[i + j] += a[i] * b[j];
  } else {
    int k = n / 2;
    int *asum, *bsum, *mult_sum;
    int *t1, *t2;
    int *s1, *s2, *s3, *s4;

    asum = calloc(k, sizeof(int));
    bsum = calloc(k, sizeof(int));
    mult_sum = calloc(n, sizeof(int));

    for (i = 0; i < k; ++i) {
      asum[i] = a[i] + a[k + i];
      bsum[i] = b[i] + b[k + i];
    }
    p_mult_kar(asum, bsum, mult_sum, k);

    p_mult_kar(a, b, c, k);
    p_mult_kar(a + k, b + k, c + n, k);

    t1 = mult_sum;
    t2 = mult_sum + k;

    s1 = c;
    s2 = c + k;
    s3 = c + 2 * k;
    s4 = c + 3 * k;

    for (i = 0; i < k; i++) {
      int c1 = s2[i] + t1[i] - s1[i] - s3[i];
      int c2 = s3[i] + t2[i] - s2[i] - s4[i];
      c[k + i] = c1;
      c[n + i] = c2;
    }

    free(asum);
    free(bsum);
    free(mult_sum);
  }
}

int main() {
  int *p1, *p2, p1_len, p2_len;
  int *res, res_len;
  int i, pad = 0;

  if (scanf("%u%u", &p1_len, &p2_len) != 2) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  p1 = (int *)calloc(p1_len, sizeof(int));
  p2 = (int *)calloc(p2_len, sizeof(int));
  res_len = 2 * p1_len - 1;
  res = (int *)calloc(res_len, sizeof(int));

  for (i = 0; i < p1_len; ++i) {
    if (scanf("%d", &p1[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  for (i = 0; i < p2_len; ++i) {
    if (scanf("%d", &p2[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  p_mult_kar(p1, p2, res, p1_len);

  for (i = res_len - 1; i >= 0; --i)
    if (res[i] == 0)
      pad += 1;
    else
      break;

  print_arr(res, res_len - pad);

  free(p1);
  free(p2);
  return 0;
}