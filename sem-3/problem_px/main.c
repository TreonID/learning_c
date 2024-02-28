#include <stdio.h>
#include <stdlib.h>

const int N = 2;

void print_arr(unsigned const *arr, unsigned len) {
  unsigned i;
  for (i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void m_equal(unsigned (*A)[N], unsigned (*B)[N]) {
  for (int i = 0; i < N*N; ++i)
    (*A)[i] = (*B)[i];
}

void m_init(unsigned (*A)[N]) {
  for (int i = 0; i < N*N; ++i)
    (*A)[i] = 0;
}

void m_mod(unsigned (*A)[N], unsigned m, unsigned (*R)[N]) {
  for (int i = 0; i < N * N; ++i)
    (*R)[i] = (*A)[i] % m;
}


void multNxN(unsigned (*A)[N], unsigned (*B)[N], unsigned m, unsigned (*R)[N]) {
  for (int i = 0; i < N*N; ++i)
    (*R)[i] = 0;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      for (int k = 0; k < N; ++k)
        (*R)[i * N + j] += (*A)[i * N + k] * (*B)[k * N + j] % m;

  for (int i = 0; i < N * N; ++i)
    (*R)[i] %= m;
}


void powNxN(unsigned (*A)[N], unsigned k, unsigned m) {
  unsigned len = N;
  unsigned mult[N * N];
  unsigned prod[N * N];
  unsigned temp[N * N];

  m_init(&mult);
  m_init(&prod);
  m_init(&temp);

  m_mod(A, m, &mult);
  for (int i = 0; i < len; i++)
    prod[i + len * i] = 1;

  while (k > 0) {
    if ((k % 2) == 1) {
      multNxN(&prod, &mult, m, &temp);
      m_equal(&prod, &temp);
      k = k - 1;
    }
    multNxN(&mult, &mult, m, &temp);
    m_equal(&mult, &temp);
    k = k / 2;
  }
  m_equal(A, &prod);
}

int main() {
  unsigned a[4] = {10, 20, 30, 40};

  powNxN(&a, 2, 5000);
  print_arr(a, 4);
}