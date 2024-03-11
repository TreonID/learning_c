#include <stdio.h>
#include <stdlib.h>

const int K = 31, MOD = 6e6+23;

int get_hash(char *str, unsigned len) {
  long long h = 0;
  for (unsigned i = 0; i < len; ++i) {
    int x = (int)(str[i] - 'a' + 1);
    h = (h * K + x) % MOD;
  }
  return h;
}

int main() {
  unsigned ans_count, haystack_len, needle_len;
  char *haystack, *needle;
  int *h_table;
  long long h = 0;

  h_table = calloc(MOD, sizeof(struct node_t *));

  if (scanf("%u", &ans_count) != 1) {
    fprintf(stderr, "Input error - ans_count\n");
    abort();
  }

  if (scanf("%u\n", &haystack_len) != 1) {
    fprintf(stderr, "Input error - haystak_len\n");
    abort();
  }

  // Чиатаем строку и сразу считаем хэши для слов
  haystack = calloc(haystack_len + 1, sizeof(char));
  for (unsigned i = 0; i < haystack_len; ++i) {
    char c;
    if (scanf("%c", &c) != 1) {
      fprintf(stderr, "Input error - haystack\n");
      abort();
    }
    haystack[i] = c;

    if (c != ' ') {
      int x = (int)(c - 'a' + 1);
      h = (h * K + x) % MOD;
    } else {
      h_table[h] += 1;
      h = 0;
    }
  }
  h_table[h] += 1;
  h = 0;

  if (scanf("%u\n", &needle_len) != 1) {
    fprintf(stderr, "Input error - needle_len\n");
    abort();
  }

  // Читаем строку и сразу считаем хэши для слов 
  // и выводим их количество из h_table
  needle = calloc(needle_len + 1, sizeof(char));
  for (unsigned i = 0; i < needle_len; ++i) {
    char c;
    if (scanf("%c", &c) != 1) {
      fprintf(stderr, "Input error - needle\n");
      abort();
    }
    needle[i] = c;

    if (c != ' ') {
      int x = (int)(c - 'a' + 1);
      h = (h * K + x) % MOD;
    } else {
      printf("%d ", h_table[h]);
      h = 0;
    }
  }
  printf("%d\n", h_table[h]);

  free(h_table);
  free(haystack);
  free(needle);
}