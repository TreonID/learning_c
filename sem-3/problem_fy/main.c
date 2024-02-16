#include <stdio.h>
#include <stdlib.h>

struct data_t {
  int *arr;
  unsigned len;
};

void print_data(const struct data_t data);

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
  unsigned max_pos = d.len - 1, rand_pos;
  for (int i = max_pos; i > 0; --i) {
    rand_pos = myrand() % i;
    printf("SWAP: %d %d\n", i, rand_pos);
    swap(&d.arr[i], &d.arr[rand_pos]);
    print_data(d);
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
  int i;
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

  shuffle_fy(&d);
  print_data(d);

  free(d.arr);
}