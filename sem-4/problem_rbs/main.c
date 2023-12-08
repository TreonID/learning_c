#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct bucket {
  struct node_t *list;
  int min, max;
};

int get_max(int *inp, int count) {
  int max = 0;
  for (int i = 0; i < count; i++) 
    if (inp[i] > max)
      max = inp[i];
  return max;
}

void make_bucket(int *inp, int count) {
  int max = get_max(inp, count);
  int bucket_size = max / count;
  struct bucket buckets[count];
  int add_left;

  if (bucket_size < 1) {
    fprintf(stderr, "Bucket less then 1\n");
    abort();
  }

  for(int i = 0; i < count; i++) {
    add_left = (i == 0) ? 0: 1;
    buckets[i].min = i * bucket_size + add_left;
    buckets[i].max = (i == count - 1) ? max : (i + 1) * bucket_size;
#if 0
    printf("Bucket %d Min: %d Max: %d\n", i + 1, buckets[i].min, buckets[i].max);
#endif
  }
  
#if 0
  printf("Max is %d\nBucket size is %d\n", max, bucket_size);
#endif
}

int main() {
  int count, res;
  int *inp; 
  res = scanf("%d", &count);
  if (res != 1) {
    fprintf(stderr, "Input error\n");
    return 1;
  }

  inp = (int *)calloc(count, sizeof(int));
  for(int i = 0; i < count; i++) {
    res = scanf("%d", &inp[i]);
    if (res != 1) {
      fprintf(stderr, "Input error\n");
      free(inp);
      return 1;
    }
  }
  make_bucket(inp, count);

  free(inp);
}

