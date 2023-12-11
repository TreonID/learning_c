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

struct node_t *list_loop_knot(struct node_t *top) {
  struct node_t *trtl, *rab;
  trtl = top;
  rab = top;
  while (trtl != NULL) {
    if (rab->next == NULL) {
      return NULL;
    }
    rab = rab->next;
    if (rab == trtl) {
      return rab;
    }
    if (rab->next == NULL) {
      return NULL;
    }
    rab = rab->next;
    if (rab == trtl) {
      return rab;
    }
    if (trtl->next == NULL) {
      return NULL;
    }
    trtl = trtl->next;
  }
  return NULL;
}

int loop_len(struct node_t *top) {
  struct node_t *knot, *node;
  int i = 0;
  knot = list_loop_knot(top);

  if (knot) {
    node = knot;
   
    while (node->next != knot) {
      node = node->next;
      i++;
    }
    return ++i;
  } 
  return 0;
}

int main() {
  struct node_t *n1, *n2, *n3;
  n3 = make_node(NULL, 6);
  n2 = make_node(n3, 4);
  n1 = make_node(n2, 2);
  n3->next = n2;
  print_limit_list(n1, 10);
  printf("Loop length: %d\n", loop_len(n1));
}
