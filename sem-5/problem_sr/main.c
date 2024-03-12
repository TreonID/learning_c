#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_string(char **str, int len) {
  *str = calloc(len + 1, sizeof(char));
  for (int i = 0; i < len; ++i) {
    char c;
    if (scanf("%c", &c) != 1) {
      fprintf(stderr, "Input error read_string\n");
      abort();
    }
    (*str)[i] = c;
  }
  (*str)[len] = '\0';
}

int main() {
  char *needle = NULL, *haystack = NULL;
  int n_len, h_len;
  char *fpos;

  if (scanf("%d ", &n_len) != 1) {
    fprintf(stderr, "Input error n_len\n");
    abort();
  }

  read_string(&needle, n_len);

  if (scanf("%d ", &h_len) != 1) {
    fprintf(stderr, "Input error h_len\n");
    abort();
  }

  read_string(&haystack, h_len);

  fpos = haystack;

  while ((fpos = strstr(fpos, needle)) != NULL) {
    char *buf = calloc(n_len, sizeof(char));

    int j = n_len;
    for (int i = 0; i < n_len; ++i)
      buf[--j] = *(fpos + i);
    for (int i = 0; i < n_len; ++i)
      *(fpos + i) = buf[i];

    fpos += n_len;
    free(buf);
  }

  printf("%s\n", haystack);

  free(needle);
  free(haystack);
}