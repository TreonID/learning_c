//
// Problem MS — слияние для сортировки слиянием
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_arr(int const *arr, unsigned len);
void xprint_arr(char const *arr, int const *sizes, int nelts);
int cmp_charint(void *lhs, int lsz, void *rhs, int rsz);

void print_arr(int const *arr, unsigned len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i != len - 1) printf(" ");
  }
  printf("\n");
}

void xprint_arr(char const *arr, int const *sizes, int nelts) {
  int pos = 0;

  for (int i = 0; i < nelts; ++i) {
    if (sizes[i] == 1)
      printf("(char)%d", arr[pos]);
    if (sizes[i] == 4)
      printf("(int)%d", *(int *)(arr + pos));
    pos += sizes[i];

    if (i != nelts - 1) printf(" ");
  }
  printf("\n");
}

int cmp_charint(void *lhs, int lsz, void *rhs, int rsz) {
  int lv = (lsz == 1) ? *(char *)lhs : *(int *)lhs;
  int rv = (rsz == 1) ? *(char *)rhs : *(int *)rhs;
  return lv - rv;
}



typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);
int ac_pos(int *sizes, int index);
void copy(void *a, void *b, int count);
void xmsort_imp(void *mem, int *sizes, xcmp_t cmp, int l, int r);
void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);
void xmerge(void *mem, int *sizes, xcmp_t cmp, int l, int m, int r);


int ac_pos(int *sizes, int index) {
  int pos = 0;
  for (int i = 0; i < index; ++i)
    pos += sizes[i];
  return pos;
}

void copy(void *a, void *b, int count) {
  char *ca = (char *)a;
  char *cb = (char *)b;
  for (int i = 0; i < count; i++) {
    ca[i] = cb[i];
  }
}

void xmerge(void *mem, int *sizes, xcmp_t cmp, int l, int m, int r) {
  int len_bytes = 0;
  int len_sizes = 1 + r - l;

  char *tmp;
  int tmp_pos = 0;
  int *tmp_sizes;
  int s_pos = 0;

  char *p1, *p2, *p1_max, *p2_max;
  int pos1 = l, pos2 = m + 1;

  char *cmem = (char *)mem;
  for (int i = l; i <= r; ++i)
    len_bytes += sizes[i];

  tmp = calloc(len_bytes, sizeof(char));
  tmp_sizes = calloc(len_sizes, sizeof(int));

  p1 = &cmem[ac_pos(sizes, l)];
  p2 = &cmem[ac_pos(sizes, m + 1)];
  p1_max = &cmem[ac_pos(sizes, m)];
  p2_max = &cmem[ac_pos(sizes, r)];

  while (p1 <= p1_max && p2 <= p2_max) {
    if (cmp(p1, sizes[pos1], p2, sizes[pos2]) < 0) {
      copy(&tmp[tmp_pos], p1, sizes[pos1]);
      p1 += sizes[pos1];
      tmp_pos += sizes[pos1];
      tmp_sizes[s_pos] = sizes[pos1];
      s_pos += 1;
      pos1 += 1;
    } else {
      copy(&tmp[tmp_pos], p2, sizes[pos2]);
      p2 += sizes[pos2];
      tmp_pos += sizes[pos2];
      tmp_sizes[s_pos] = sizes[pos2];
      s_pos += 1;
      pos2 += 1;
    }
  }

  if (p1 <= p1_max) {
    while (p1 <= p1_max) {
      copy(&tmp[tmp_pos], p1, sizes[pos1]);
      p1 += sizes[pos1];
      tmp_pos += sizes[pos1];
      tmp_sizes[s_pos] = sizes[pos1];
      s_pos += 1;
      pos1 += 1;
    }
  }

  if (p1 <= p2_max) {
    while (p2 <= p2_max) {
      copy(&tmp[tmp_pos], p2, sizes[pos2]);
      p2 += sizes[pos2];
      tmp_pos += sizes[pos2];
      tmp_sizes[s_pos] = sizes[pos2];
      s_pos += 1;
      pos2 += 1;
    }
  }

  for (int i = 0; i < len_bytes; ++i) {
    cmem[ac_pos(sizes, l) + i] = tmp[i];
  }

  for (int i = 0; i < len_sizes; ++i)
    sizes[l + i] = tmp_sizes[i];

  free(tmp);
  free(tmp_sizes);
}

void xmsort_imp(void *mem, int *sizes, xcmp_t cmp, int l, int r) {
  int m = 0;
  if (l >= r) return;
  m = (l + r) / 2;
  xmsort_imp(mem, sizes, cmp, l, m);
  xmsort_imp(mem, sizes, cmp, m + 1, r);
  xmerge(mem, sizes, cmp, l, m, r);
}

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp) {
  xmsort_imp(mem, sizes, cmp, 0, nelts - 1);
}

int main() {
  int len = 4, pos = 0;
  int input[4] = {1004, 3, 5, 2002};
  int sizes[4] = {4, 1, 1, 4};
  char *arr;
  unsigned byte_size = 0;

  for (int i = 0; i < len; ++i)
    byte_size += sizes[i];

  arr = calloc(byte_size, sizeof(char));

  for (int i = 0; i < len; ++i) {
    if (sizes[i] == 4) {
      *(int *)(arr + pos) = input[i];
    }
    if (sizes[i] == 1) {
      arr[pos] = (char)input[i];
    }
    pos += sizes[i];
  }

  xprint_arr(arr, sizes, len);
  xmsort(arr, sizes, len, cmp_charint);
  xprint_arr(arr, sizes, len);

  free(arr);
}