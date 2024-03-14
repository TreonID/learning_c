/* Problem RXM — переворот подстрок с поиском регекспом */

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 10

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

void reverse(char *start, int len) {
  char *buffer = calloc(len + 1, sizeof(char));
  int j = len;

  for (int i = 0; i < len; ++i)
    buffer[--j] = *(start + i);

  memcpy(start, buffer, len);

  free(buffer);
}

void make_reverse(char *haystack, int h_len, char const *needle, int n_len) {
  int res;
  char word[100], n_word[100];
  char *cpos = haystack;
  int w_len = 0;

  regex_t regex;
  regmatch_t matches[MAX_MATCHES];
  res = regcomp(&regex, needle, REG_EXTENDED);
  if (res) {
    fprintf(stderr, "Regex comp failed\n");
    abort();
  }

  res = regexec(&regex, haystack, MAX_MATCHES, matches, 0);
  if (!res) {
    w_len = matches[0].rm_eo - matches[0].rm_so;
    memcpy(word, haystack + matches[0].rm_so, w_len);
    word[w_len] = '\0';
    strcpy(n_word, word);
    reverse(n_word, w_len);
#if 0
    printf("Word>%s<\n", word);
    printf("Reverse Word>%s<\n", n_word);
#endif
  }

  if (w_len != 0)
    while ((cpos = strstr(cpos, word)) != NULL) {
      memcpy(cpos, n_word, w_len);
      cpos += w_len;
    }

  regfree(&regex);
}

int main() {
  char *needle, *haystack;
  int n_len, h_len;

  n_len = read_int_s();
  read_string(&needle, n_len);
  h_len = read_int_s();
  read_string(&haystack, h_len);

  make_reverse(haystack, h_len, needle, n_len);

  printf("%s\n", haystack);

  free(needle);
  free(haystack);
}