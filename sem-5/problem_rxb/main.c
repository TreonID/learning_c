/* Problem RXB — простые регулярные выражения */

#include <regex.h>
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

int read_string(char **str) {
  int size = 10;
  char c;
  int count = 0;
  char *tmp = calloc(size, sizeof(char));
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }

  while (scanf("%c", &c) == 1) {
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

int is_email(char *str) {
  int res;
  const char *cregex = "^[[:alnum:].][[:alnum:].]*@[[:alpha:]][[:alpha:].]*[.][[:alpha:]][[:alpha:]]*[[:space:]]*$";
  regex_t regex;
  regcomp(&regex, cregex, 0);
  res = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  return (res == 0) ? 1 : 0;
}

int main() {
  char *str;
  int res;

  read_string(&str);
  res = is_email(str);

  printf("%d\n", res);

  free(str);
}