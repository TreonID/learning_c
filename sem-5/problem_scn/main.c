#include <stdio.h>
#include <stdlib.h>

int main() {
  char c;
  int sum = 0;

  while (scanf("%c", &c) != -1)
    sum += c;

  printf("%d\n", sum);

}