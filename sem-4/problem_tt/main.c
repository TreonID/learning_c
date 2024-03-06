/*
** Problem TT — дерево из обходов
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

void print_arr(const int *arr, int len) {
  int i;
  for (i = 0; i < len; ++i)
    printf("%d", arr[i]);
  printf("\n");
}

struct tree_t *make_tree(int data) {
  struct tree_t *tmp = calloc(1, sizeof(struct tree_t));
  tmp->data = data;
  return tmp;
}

int find(const int *arr, int left, int right, int data) {
  for (int i = left; i <= right; ++i)
    if (arr[i] == data)
      return i;
  return -1;
}

struct tree_t *build_tree(int *arr_pre, int *arr_in, int left, int right) {
  struct tree_t *tmp;
  int mid;
  static int pre_index = 0;
  
  if (left > right)
    return NULL;

  tmp = make_tree(arr_pre[pre_index++]);
  if (left == right)
    return tmp;

  mid = find(arr_in, left, right, tmp->data);
  assert(mid >= 0);
  tmp->left = build_tree(arr_pre, arr_in, left, mid - 1);
  tmp->right = build_tree(arr_pre, arr_in, mid + 1, right);
  return tmp;
}

void print_post(struct tree_t *top) {
  if (top == NULL)
    return;

  print_post(top->left);
  print_post(top->right);
  printf("%d ", top->data);
}

int main() {
  int n, *arr_in, *arr_pre;
  struct tree_t *tree;

  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  arr_in = calloc(n, sizeof(int));
  arr_pre = calloc(n, sizeof(int));

  for (int i = 0; i < n; ++i) {
    if (scanf("%d", &arr_pre[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }
  for (int i = 0; i < n; ++i) {
    if (scanf("%d", &arr_in[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  tree = build_tree(arr_pre, arr_in, 0, n - 1);

  print_post(tree);
  printf("\n");

  free(arr_in);
  free(arr_pre);
}