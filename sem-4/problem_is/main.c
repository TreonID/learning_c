/*
** Problem IS — проверка поисковости
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

// START SOLUTION

int is_bst(struct tree_t *top, int range_min, int range_max) {
  int left, right;
  if (top == NULL)
    return 1;
  if (top->data < range_min || top->data > range_max)
    return 0;
  
  left = is_bst(top->left, range_min, top->data - 1);
  right = is_bst(top->right, top->data + 1, range_max);

  return left && right;
}

int check_is_bst(struct tree_t *top) {
  return is_bst(top, INT_MIN, INT_MAX);
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
  tree->right->right->left = make_tree(10);
  tree->right->right->right = make_tree(8);

  printf("%d\n", check_is_bst(tree));
  return 0;
}