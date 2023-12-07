#include <stdio.h>

struct node_t {
  struct node_t *next;
  int data;
  int count;
  int count2;
};

int main() {
  int max = 670;
  printf("%d\n", max / 8 + 1);
}
