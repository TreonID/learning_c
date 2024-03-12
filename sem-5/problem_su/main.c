#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char *strstrci(char const *needle, char const *haystack) {
  unsigned h_len = strlen(haystack), i = 0;
  unsigned n_len = strlen(needle);
  char *buf_h = calloc(h_len + 1, sizeof(char));
  char *buf_n = calloc(n_len + 1, sizeof(char));
  char const *cur = haystack;
  char *t_pos;

  while(cur < (haystack + h_len))
    buf_h[i++] = tolower(*cur++);
  
  i = 0;
  cur = needle;
  while(cur < (needle + n_len))
    buf_n[i++] = tolower(*cur++);

  t_pos = strstr(buf_h, buf_n);

  if (t_pos != NULL)
    return (char *)(haystack + (t_pos - buf_h));
  return NULL;
}

int main() {
  char const *needle = "eLL", *src = "abracadaBra_HELLO";
  printf("RESULT: %s\n", strstrci(needle, src));
  // char *pos1, *pos2, *pos3;
  // pos1 = strstrci(needle, src);
  // assert(pos1 != NULL);
  // pos2 = strstrci(needle, pos1 + 2);
  // assert(pos2 != NULL);
  // pos3 = strstrci(needle, pos2 + 2);
  // assert(pos3 == NULL);
}