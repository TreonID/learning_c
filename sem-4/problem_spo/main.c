/*
** Problem IPO — preorder traversal iterative 
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

// START SOLUTION

struct stacknode {
  struct stacknode *next;
  struct tree_t *data;
};

void push(struct stacknode **stack, struct tree_t *data) {
  struct stacknode *tmp;
  if (data == NULL)
    return;
  tmp = calloc(1, sizeof(struct stacknode));
  tmp->data = data;
  tmp->next = *stack;
  *stack = tmp;
}

struct tree_t *pop(struct stacknode **stack) {
  struct tree_t *data;
  struct stacknode *next;

  if (*stack == NULL)
    return NULL;

  data = (*stack)->data;
  next = (*stack)->next;

  free(*stack);
  *stack = next;
  return data;
}

void print_pre(struct tree_t *top) {
  struct stacknode *stack = NULL;
  push(&stack, top);

  while (stack != NULL) {
    struct tree_t *tmp = pop(&stack);
    printf("%d ", tmp->data);
    push(&stack, tmp->right);
    push(&stack, tmp->left);
  }
  printf("\n");
}

// END SOLUTION

struct tree_t *make_tree(int data) {
  struct tree_t *tmp = calloc(1, sizeof(struct tree_t));
  tmp->data = data;
  return tmp;
}

int main() {
  struct tree_t *tree;

  tree = make_tree(4);
  tree->left = make_tree(2);
  tree->left->left = make_tree(1);
  tree->right = make_tree(6);
  tree->right->left = make_tree(5);
  tree->right->right = make_tree(9);
  tree->right->right->left = make_tree(8);
  tree->right->right->right = make_tree(10);

  print_pre(tree);
}