#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *str, char const *from, char const *to) {
  char *fpos = str, *buf, *cur = str;
  int from_len = strlen(from);
  int str_len = strlen(str);
  int to_len = strlen(to);
  int count_from = 0;
  int new_len, i = 0;

  while ((fpos = strstr(fpos, from)) != NULL) {
    fpos += from_len;
    count_from++;
  }

  new_len = str_len - (from_len * count_from) + (to_len * count_from);
  buf = calloc(new_len + 1, sizeof(char));
  if (buf == NULL) {
    fprintf(stderr, "Memory allocation error!\n");
    abort();
  }
  
  fpos = str;
  while ((fpos = strstr(fpos, from)) != NULL) {
    while (cur < fpos)
      buf[i++] = *cur++;
    buf[i] = '\0';
    buf = strcat(buf, to);
    i += to_len;
    fpos += from_len;
    cur += from_len;
  }
  while (cur < (str + str_len))
    buf[i++] = *cur++;
  buf[i] = '\0';

  return buf;
}

int main() {
  const char *s1 = "Hello, \%u, how are you, \%u?";
  const char *from = "\%u";
  const char *to = "Eric, the Blood Axe";
  char *str = calloc(strlen(s1) + 1, sizeof(char));
  strcpy(str, s1);

  str = replace(str, from, to);
  printf("%s\n", str);
  free(str);
}