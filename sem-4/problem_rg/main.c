#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

typedef int (*generator_t)(int);

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

int func1(int x) { return (x + 2) % 5; }
int func2(int x) { return (x + 2) % 5 + 1; }
int func3(int x) { return (x + 2) % 5 + 3; }
int func4(int x) { return (3 * x + 2) % 5 + 4; }

struct node_t *find_in_list(struct node_t *list, int needle) {
  struct node_t *node;
  if (!list) return NULL;
  for (node = list; node != NULL; node = node->next) {
    if (node->data == needle)
      return node;
  }
  return NULL;
}

unsigned cycle_len(generator_t gen) {
  struct node_t *knot = NULL, *list = NULL, *prev = NULL, *node;
  int x = gen(0); 
  list = make_node(NULL, 0);
  prev = list;

  while (knot == NULL) {
    knot = find_in_list(list, x);
    if (knot != NULL) {
      prev->next = knot;
      break;
    }
    node = make_node(NULL, x);
    prev->next = node;
    prev = node;
    x = gen(x);
  }
  return loop_len(list);  
}

int main() {
  printf("Func1: %d\n", cycle_len(func1)); 
  printf("Func2: %d\n", cycle_len(func2)); 
  printf("Func3: %d\n", cycle_len(func3)); 
  printf("Func4: %d\n", cycle_len(func4)); 
}
