/*
** Problem HWS — алгоритм TimSort
*/

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

const int RUN = 32;

struct line_t {
  int *val;
  int sort_val;
  int len;
};

void print_arr(int const *arr, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1)
      printf(" ");
  }
  printf("\n");
}

int min(int a, int b) {
  return (a > b) ? b : a;
}

void xins_sort(struct line_t arr[], int left, int right) {
  int i;
  for (i = left + 1; i <= right; i++) {
    struct line_t temp = arr[i];
    int j = i - 1;
    while (j >= left && arr[j].sort_val > temp.sort_val) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = temp;
  }
}

void copy_line(struct line_t *a, struct line_t *b) {
  a->len = b->len;
  a->sort_val = b->sort_val;
  memcpy(a->val, b->val, b->len * sizeof(int));
}

void xmerge(struct line_t arr[], int l, int m, int r) {
  int len1 = m - l + 1, len2 = r - m;
  struct line_t *left, *right;
  int i = 0;
  int j = 0;
  int k = l;

  left = calloc(len1, sizeof(struct line_t));
  right = calloc(len2, sizeof(struct line_t));

  for (i = 0; i < len1; i++) {
    left[i].val = calloc(arr[l + i].len, sizeof(int));
    copy_line(&left[i], &arr[l + i]);
  }
  for (i = 0; i < len2; i++) {
    right[i].val = calloc(arr[m + 1 + i].len, sizeof(int));
    copy_line(&right[i], &arr[m + 1 + i]);
  }

  i = 0;
  j = 0;

  while (i < len1 && j < len2) {
    if (left[i].sort_val <= right[j].sort_val) {
      copy_line(&arr[k], &left[i]);
      i++;
    } else {
      copy_line(&arr[k], &right[j]);
      j++;
    }
    k++;
  }

  while (i < len1) {
    copy_line(&arr[k], &left[i]);
    k++;
    i++;
  }

  while (j < len2) {
    copy_line(&arr[k], &right[j]);
    k++;
    j++;
  }

  free(left->val);
  free(right->val);
  free(left);
  free(right);
}

void xtim_sort(struct line_t arr[], int n) {
  int i, size, left;
  for (i = 0; i < n; i += RUN)
    xins_sort(arr, i, min((i + RUN - 1), (n - 1)));

  for (size = RUN; size < n; size = 2 * size) {
    for (left = 0; left < n; left += 2 * size) {
      int mid = left + size - 1;
      int right = min((left + 2 * size - 1), (n - 1));

      if (mid < right) {
        xmerge(arr, left, mid, right);
      }
    }
  }
}

int main() {
  int len, len_in_line, n;
  int i, j;
  struct line_t *lines;

  if (scanf("%d%d%d", &len, &len_in_line, &n) != 3) {
    fprintf(stderr, "Input error");
    abort();
  }

  lines = calloc(len, sizeof(struct line_t));
  if (lines == NULL) {
    fprintf(stderr, "Memory allocation error");
    abort();
  }

  for (i = 0; i < len; ++i) {
    struct line_t *tmp_line;
    tmp_line = calloc(1, sizeof(struct line_t));
    tmp_line->val = calloc(len_in_line, sizeof(int));
    if (tmp_line == NULL || tmp_line->val == NULL) {
      fprintf(stderr, "Memory allocation error");
      abort();
    }

    for (j = 0; j < len_in_line; ++j)
      if (scanf("%d", &tmp_line->val[j]) != 1) {
        fprintf(stderr, "Input error");
        abort();
      }
    tmp_line->len = len_in_line;
    tmp_line->sort_val = tmp_line->val[n];
    lines[i] = *tmp_line;
    free(tmp_line);
  }

  xtim_sort(lines, len);

  for (i = 0; i < len; ++i) {
    struct line_t l = lines[i];
    printf("%d", l.val[i % len_in_line]);
    if (i < len - 1)
      printf(" ");
  }
  printf("\n");

  for (i = 0; i < len; ++i) {
    struct line_t l = lines[i];
    free(l.val);
  }
  free(lines);

  return 0;
}