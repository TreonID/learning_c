#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned R = 1, Q = 1000003;

unsigned long long pow_mod(unsigned n, unsigned k, unsigned m);

// подсчитать хеш строки от start до fin
int get_hash(const char *start, const char *fin) {
  int res = 0;
  int n = (fin - start) - 1;
  while (start != fin) {
    res += ((*start) * pow_mod(R, n, Q)) % Q;
    n -= 1;
    start++;
  }
  return res % Q;
}

// обновить хеш current, удалив из него cprev и добавив в него cnext
// здесь n это pow_mod(R, right - 1, Q)
// возвращает новый хеш
int update_hash(int current, int n, char cprev, char cnext) {
  return ((current - cprev * n) * R + cnext) % Q;
}

// raise n to power k modulo m
unsigned long long pow_mod(unsigned n, unsigned k, unsigned m) {
  unsigned mult = n % m;
  unsigned prod = 1;
  while (k > 0) {
    if ((k % 2) == 1) {
      prod = (prod * mult) % m;
      k = k - 1;
    }
    mult = (mult * mult) % m;
    k = k / 2;
  }
  return prod;
}

// Start solution

// возвращает номер позиции на которой needle расположена внутри haystack
// или -1 если ничего не найдено
int rabin_karp(const char *needle, const char *haystack) {
  unsigned n, target, cur, left = 0, right = strlen(needle);
  int finded = 0;
  if (strlen(haystack) < strlen(needle))
    return -1;

  target = get_hash(needle, needle + right);
  cur = get_hash(haystack, haystack + right);

  n = pow_mod(R, right - 1, Q);

  while (finded == 0 && haystack[right] != 0) {
    cur = update_hash(cur, n, haystack[left], haystack[right]);

    if (target == cur) {
      finded = 1;
      for (unsigned i = 0; i < strlen(needle); ++i)
        if (haystack[left + 1 + i] != needle[i]) {
          finded = 0;
          break;
        }
    }

    if (finded)
      return (int)left;

    left += 1;
    right += 1;

  }

  return -1;
}

// End solution

int main() {
  int h_n, n_n;
  int left = 0;
  int count = 0, rk = 0;
  char *needle, *haystack;

  if (scanf("%d", &h_n) != 1) {
    abort();
  }
  haystack = calloc(h_n + 1, sizeof(char));
  if (scanf("%s", haystack) == 0) {
    abort();
  }

  if (scanf("%d", &n_n) != 1) {
    abort();
  }
  needle = calloc(n_n + 1, sizeof(char));
  if (scanf("%s", needle) == 0) {
    abort();
  }

  while (left < h_n) {
    rk = rabin_karp(needle, haystack + left);
    if (rk != -1) {
      count += 1;
      left += rk + 1;
    } else {
      
      left += 1;
    }
  }
    
  printf("%d\n", count);

  free(needle);
  free(haystack);
  return 0;
}