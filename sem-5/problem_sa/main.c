#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strcat_r(char *dest, const char *src, int *bufsz) {
  int new_len = *bufsz + strlen(src);
  char *tc = (char *)realloc(dest, new_len);
  if (tc != NULL) {
    tc = strcat(tc, src);
    *bufsz = new_len;
    return tc;
  } else {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }
}

int main() {
  char *str1 = "Hello";
  char *str2 = ", world!";

  int bufsz = 6;
  char *dest = calloc(bufsz, sizeof(char));
  dest = strcpy(dest, str1);
  dest = strcat_r(dest, str2, &bufsz);

  printf("[]%s[]\n", dest);
  free(dest);
}