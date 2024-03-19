/* Homework HWK — алгоритм КМП */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fprintf(stderr, "Input error int\n");
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

void patpreproc(char const *needle, int *needle_lps) {
  int k = 0;
  int count = strlen(needle);

  for (int i = 1; i < count; i++) {
    if (tolower(needle[i]) == tolower(needle[k])) {
      needle_lps[i] = ++k;
    } else if (k == 0) {
      needle_lps[i] = 0;
    } else {
      k = needle_lps[k - 1];
      i--;
    }
  }
}

char *strstrci(char const *needle, int const *needle_lps, char const *haystack) {
  int h_len = strlen(haystack);
  int n_len = strlen(needle);
  int k = 0;

  for (int i = 1; i < h_len; ++i) {
    while (k > 0 && (tolower(haystack[i]) != tolower(needle[k + 1])))
      k = needle_lps[k - 1];
    
    if (tolower(haystack[i]) == tolower(needle[k]))
      k += 1;
    
    if (k == n_len)
      return (char *)(haystack + (i - n_len + 1));

  }

  return NULL;
}


char *strstrci_ed1(char const *needle, int const *needle_lps, char const *haystack) {
  int h_len = strlen(haystack);
  int n_len = strlen(needle);
  int i = 0;

  while (i <= h_len - n_len) {
    int eq = 0;
    int pad = 1;

    for (int j = 0; j < n_len; j++)
      if (tolower(*(haystack + i + j)) == tolower(needle[j]))
        eq += 1;
      else
        break;

    if (eq == n_len)
      return (char *)(haystack + i);

    pad = eq - needle_lps[eq - 1];
    i += (pad > 0) ? pad : 1;
  }

  return NULL;
}

int main() {
  char *needle = NULL;
  char *haystack = NULL;
  int *prf, h_len = 0, n_len = 0;
  char *res = NULL;

  h_len = read_int_s();
  read_string(&haystack, h_len);
  n_len = read_int_s();
  read_string(&needle, n_len);

  prf = calloc(n_len, sizeof(int));
  patpreproc(needle, prf);

  res = strstrci(needle, prf, haystack);
  if (res != NULL)
    printf("%s\n", res);

  free(prf);
}