#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *make_node(struct node_t *next, int data) {
  struct node_t *node;
  node = calloc(1, sizeof(struct node_t));
  node->next = next;
  node->data = data;
  return node;
}

void print_limit_list(const struct node_t *list, int limit) {
  const struct node_t *node;
  int i = limit;
  for(node = list; node != NULL; node = node->next) {
    printf("%d -> ", node->data);

    i--;
    if (i == 0) {
      printf("Limit reached.");
      break;
    }
  }
  printf("\n");
}

int list_is_a_loop(struct node_t *top) {
  struct node_t *trtl, *rab;
  trtl = top;
  rab = top;
  while (trtl != NULL) {
    if (rab->next == NULL) {
      return 0;
    }
    rab = rab->next;
    if (rab == trtl) {
      return 1;
    }
    if (rab->next == NULL) {
      return 0;
    }
    rab = rab->next;
    if (rab == trtl) {
      return 1;
    }
    if (trtl->next == NULL) {
      return 0;
    }
    trtl = trtl->next;
  }
  return 0;
}

int main() {
  struct node_t *n1, *n2, *n3;
  n3 = make_node(NULL, 6);
  n2 = make_node(n3, 4);
  n1 = make_node(n2, 2);
  n3->next = n1;
  print_limit_list(n1, 10);
  printf("Loop: %d\n", list_is_a_loop(n1));
}
