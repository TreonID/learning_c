/*
** Problem NO — натуральный порядок
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

struct tree_t *make_tree(int data) {
  struct tree_t *tmp = calloc(1, sizeof(struct tree_t));
  tmp->data = data;
  return tmp;
}

void add_to_tree(struct tree_t *top, int data) {
  if (top == NULL)
    top = make_tree(data);

  if (data < top->data) {
    if (top->left == NULL)
      top->left = make_tree(data);
    else
      add_to_tree(top->left, data);
  } else {
    if (top->right == NULL)
      top->right = make_tree(data);
    else
      add_to_tree(top->right, data);
  }
}

void print_pre(struct tree_t *top) {
  if (top == NULL)
    return;
  printf("%d ", top->data);
  print_pre(top->left);
  print_pre(top->right);
}

void del_tree(struct tree_t *top) {
  if (top == NULL)
    return;
  del_tree(top->left);
  del_tree(top->right);
  free(top);
}

int main() {
  int n, *arr;
  struct tree_t *tree = NULL;

  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  arr = calloc(n, sizeof(int));

  for (int i = 0; i < n; ++i) {
    if (scanf("%d", &arr[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  tree = make_tree(arr[0]);
  for (int i = 1; i < n; ++i)
    add_to_tree(tree, arr[i]);

  print_pre(tree);
  printf("\n");

  del_tree(tree);
  free(arr);
}