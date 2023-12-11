#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *read_file(FILE *f) {
  struct node_t *list = NULL, *node = NULL;
  int n;
  while (fscanf(f, "%d", &n) == 1) {
    node = calloc(1, sizeof(struct node_t));
    node->data = n;
    node->next = list;
    list = node;
  }
  return list;
}

void print_list(const struct node_t *list) {
  const struct node_t *node;
  for (node = list; node != NULL; node = node->next) {
    printf("%d->", node->data);
  }
  printf("\n");
}

struct node_t *reverse(struct node_t *top) {
  struct node_t *first = NULL, *second = NULL, *tmp;
  if (top == NULL) return NULL;
  if (top->next == NULL) return NULL;
  first = top;
  second = top->next;
  top->next = NULL;
  while (second != NULL) {
    tmp = second->next;
    second->next = first;
    first = second;
    second = tmp;
  }
  return first;

}

int main() {
  FILE *f = fopen("input.txt", "r");
  
  if (!f) {
    perror("Error opening file");
    abort();
  }
  
  print_list(reverse(read_file(f)));

  fclose(f);
}
