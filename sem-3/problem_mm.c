#include <stdio.h>
#include <stdlib.h>

struct data_t {
  int *arr;
  unsigned len;
};

void print_mm(struct data_t *d) {
  int min, max;
  unsigned i;
  min = max = d->arr[0];
  for (i = 1; i < d->len; ++i) {
    min = (d->arr[i] < min) ? d->arr[i] : min;
    max = (d->arr[i] > max) ? d->arr[i] : max;
  }	
  printf("%d %d", min, max);
}

int main() {
  struct data_t d;
  unsigned i;

  if (scanf("%u", &d.len) != 1) 
    abort();
  if (d.len == 0) {
    printf("0 0\n");
    return 0;
  }

  d.arr = (int *)malloc(d.len * sizeof(int));

  if (d.arr == NULL) 
    abort();

  for (i=0; i < d.len; ++i) {
    if (scanf("%d", &d.arr[i]) != 1) 
      abort();
  }

  print_mm(&d);
 
  free(d.arr);

}
