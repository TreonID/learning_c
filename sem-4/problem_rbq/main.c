#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *left;
  struct node_t *right;
  unsigned char height;
  int data;
};

struct req_t {
  int min;
  int max;
};

unsigned char height(struct node_t *p) {
  return p ? p->height : 0;
}

int bfactor(struct node_t *p) {
  return height(p->right) - height(p->left);
}

void fixheight(struct node_t *p) {
  unsigned char hl = height(p->left);
  unsigned char hr = height(p->right);
  p->height = (hl > hr ? hl : hr) + 1;
}

// правый поворот вокруг p
struct node_t *rotateright(struct node_t *p) {
  struct node_t *q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

// левый поворот вокруг q
struct node_t *rotateleft(struct node_t *q) {
  struct node_t *p = q->right;
  q->right = p->left;
  p->left = q;
  fixheight(q);
  fixheight(p);
  return p;
}

// балансировка узла p
struct node_t *balance(struct node_t *p) {
  fixheight(p);
  if (bfactor(p) == 2) {
    if (bfactor(p->right) < 0)
      p->right = rotateright(p->right);
    return rotateleft(p);
  }
  if (bfactor(p) == -2) {
    if (bfactor(p->left) > 0)
      p->left = rotateleft(p->left);
    return rotateright(p);
  }
  return p;  // балансировка не нужна
}

struct node_t *make_node(int data) {
  struct node_t *tmp = calloc(1, sizeof(struct node_t));
  if (tmp == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }
  tmp->data = data;
  tmp->height = 1;
  return tmp;
}

// вставка данных k в дерево с корнем p
struct node_t *insert(struct node_t *p, int k) {
  if (!p) return make_node(k);
  if (k < p->data)
    p->left = insert(p->left, k);
  else
    p->right = insert(p->right, k);
  return balance(p);
}

void print_pre(const struct node_t *top) {
  if (top == NULL)
    return;
  printf("%d ", top->data);
  print_pre(top->left);
  print_pre(top->right);
}

void del_tree(struct node_t *top) {
  if (top == NULL)
    return;
  del_tree(top->left);
  del_tree(top->right);
  free(top);
}

void visit_range(struct node_t *top, int l, int r, int *sum) {
  if (NULL == top) return;
  if (l <= top->data && r >= top->data)
    *sum = *sum + 1;
  if (l <= top->data)
    visit_range(top->left, l, r, sum);
  if (r >= top->data)
    visit_range(top->right, l, r, sum);
}

int main() {
  struct node_t *tree = NULL;
  struct req_t *req = NULL;
  int len, r_len;

  if (scanf("%d", &len) != 1) {
    fprintf(stderr, "Input error len\n");
    abort();
  }

  for (int i = 0; i < len; ++i) {
    int tmp;
    if (scanf("%d", &tmp) != 1) {
      fprintf(stderr, "Input error tree\n");
      abort();
    }
    tree = insert(tree, tmp);
  }

  if (scanf("%d", &r_len) != 1) {
    fprintf(stderr, "Input error r_len\n");
    abort();
  }

  req = calloc(r_len, sizeof(struct req_t));
  for (int i = 0; i < r_len; ++i) {
    if (scanf("%d%d", &(req[i].min), &(req[i].max)) != 2) {
      fprintf(stderr, "Input error req\n");
      abort();
    }
  }

  for (int i = 0; i < r_len; ++i) {
    int sum = 0;
    visit_range(tree, req[i].min, req[i].max, &sum);
    printf("%d ", sum);
  }
  printf("\n");

  free(req);
  del_tree(tree);
}