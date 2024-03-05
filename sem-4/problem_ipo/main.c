/*
** Problem IPO — preorder traversal recursive
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
void print_node(struct tree_t *top) {
  if (top == NULL)
    return;

  printf("%d ", top->data);
  print_node(top->left);
  print_node(top->right);
}


void print_pre(struct tree_t *top) {
  print_node(top);
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