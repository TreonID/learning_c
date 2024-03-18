/* Problem ED — расстояние редактирования */

#include <assert.h>
#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

char *s_realloc(char *c, int new_size) {
  char *t_tmp;
  t_tmp = realloc(c, new_size);
  if (t_tmp == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }
  return t_tmp;
}

int read_int_s() {
  int tmp;
  if (scanf("%d ", &tmp) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }
  return tmp;
}

int read_string(char **str, int len) {
  int size = 10;
  char c;
  int count = 0;
  char *tmp = calloc(size, sizeof(char));
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }

  while (scanf("%c", &c) == 1 && count < len) {
    if (c == '\n')
      break;

    if (c == ' ')
      continue;

    if (count + 1 > size) {
      size *= 2;
      tmp = s_realloc(tmp, size);
    }
    tmp[count++] = c;
  }
  tmp[count] = '\0';

  size = count + 1;
  tmp = s_realloc(tmp, size);
  *str = tmp;
  return count;
}

int min(int a, int b) {
  return (a > b) ? b : a;
}

int min3(int a, int b, int c) {
  return min(min(a, b), c);
}

enum Actions { ADD = 0,
               REM,
               REP };

int build(int **V, char *str1, int len1, char *str2, int len2, int *actions, int actions_size) {
  int k, v1, v2, v3;
  for (int i = 0; i <= len1; ++i)
    for (int j = 0; j <= len2; ++j) {
      if (i == 0) {
        V[i][j] = j * actions[ADD];
        continue;
      }
      if (j == 0) {
        V[i][j] = i * actions[ADD];
        continue;
      }

      v1 = (i > 0) ? V[i - 1][j] + actions[ADD] : INT_MAX;
      v2 = (j > 0) ? V[i][j - 1] + actions[ADD] : INT_MAX;
      k = (str1[i - 1] == str2[j - 1]) ? 0 : actions[REP];
      v3 = (i > 0 && j > 0) ? V[i - 1][j - 1] + k : INT_MAX;
      V[i][j] = min3(v1, v2, v3);
    }
  return V[len1][len2];
}

void print_table(int **V, char *str1, int len1, char *str2, int len2) {
  printf("#\t");
  for (int i = 1; i <= len2; ++i) {
    printf("%c\t", str2[i - 1]);
  }
  printf("\n");
  for (int i = 0; i <= len1; ++i) {
    for (int j = 0; j <= len2; ++j) {
      if (j == 0 && i != 0)
        printf("%c ", str1[i - 1]);
      if (j == 0 && i == 0)
        printf("  ");
      printf("%d\t", V[i][j]);
    }
    printf("\n");
  }
}

int main() {
  const int actions_size = 3;
  int actions[3] = {0};
  int len1, len2;
  char *str1 = NULL, *str2 = NULL;
  int **V;
  int res;

  actions[ADD] = read_int_s();
  actions[REM] = read_int_s();
  actions[REP] = read_int_s();

  len1 = read_int_s();
  read_string(&str1, len1);
  len2 = read_int_s();
  read_string(&str2, len2);

  V = calloc(len1 + 1, sizeof(int *));
  for (int i = 0; i <= len1; i++)
    V[i] = calloc(len2 + 1, sizeof(int));

  res = build(V, str1, len1, str2, len2, actions, actions_size);
#if 0
  print_table(V, str1, len1, str2, len2);
#endif
  printf("%d\n", res);

  for (int i = 0; i <= len1; i++)
    free(V[i]);
  free(V);
  free(str1);
  free(str2);
}