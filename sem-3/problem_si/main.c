#include <stdio.h>
#include <stdlib.h>

struct data_t {
  int *arr;
  unsigned len;
};

void inssort(int *arr, int len);
int moveright(int *arr, int key, int last);
void print_data(const struct data_t data);
int myrand();
void swap(int *a, int *b);
void shuffle_fy(struct data_t *data);

void inssort(int *arr, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    int key, pos;
    key = arr[i];
    pos = moveright(arr, key, i);
    arr[pos] = key;
  }
}

int moveright(int *arr, int key, int last) {
  if (last == 0)
    return 0;
  for (int i = last - 1; i >= 0; --i)
    if (arr[i] > key)
      arr[i + 1] = arr[i];
    else
      return i + 1;
  return last;
}

int myrand() {
  static unsigned long int seed = 1;
  seed = seed * 1103515245 + 12345;
  return (unsigned int)(seed / 65536) % 32768;
}

void swap(int *a, int *b) {
  if (*a != *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
  }
}

void shuffle_fy(struct data_t *data) {
  struct data_t d = *data;
  unsigned rand_pos;
  for (int i = d.len - 1; i > 0; --i) {
    rand_pos = myrand() % (i + 1);
    swap(&d.arr[i], &d.arr[rand_pos]);
  }
}

void print_data(const struct data_t data) {
  for (int i = 0; i < data.len; ++i) {
    printf("%d", data.arr[i]);
    if (i != data.len - 1) printf(" ");
  }
  printf("\n");
}

int main() {
  int i, pos;
  struct data_t d;

  if (scanf("%u", &d.len) != 1) {
    fprintf(stderr, "Input error\n");
    abort();
  }

  if (d.len == 0) {
    printf("0\n");
    return 0;
  }

  d.arr = (int *)malloc(d.len * sizeof(int));

  if (d.arr == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    abort();
  }

  for (i = 0; i < d.len; ++i) {
    if (scanf("%d", &d.arr[i]) != 1) {
      fprintf(stderr, "Input error\n");
      abort();
    }
  }

  if (d.len == 1) {
    printf("%d\n", d.arr[0]);
    return 0;
  }

  print_data(d);
  pos = moveright(d.arr, 5, 0);
  print_data(d);
  printf("pos = %d\n", pos);
  // inssort(d.arr, d.len);
  // print_data(d);

  free(d.arr);
}