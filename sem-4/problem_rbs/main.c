#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct bucket_t {
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

void print_buckets(struct bucket_t *buckets, int count) {
  struct node_t *node;
  for (int i = 0; i < count; i++) {
    if (buckets[i].list) {
      node = buckets[i].list;
      for (; ; ) {
        printf("%d ", node->data);
        if (!(node->next))
          break;
        node = node->next;
      }
      printf("0 ");

    } else {
      printf("0 ");
    }
    
  }
  printf("\n");
}

void add_to_bucket(struct bucket_t *bucket, int inp) {
  struct node_t *element;

  element = (struct node_t *)calloc(1, sizeof(struct node_t));
  element->data = inp;
  
  if (bucket->list) {

  } else {
    bucket->list = element;
  }
}

void make_bucket(int *inp, int count) {
  int max = get_max(inp, count);
  int bucket_size = max / count;
  struct bucket_t *buckets;
  int add_left;

  if (bucket_size < 1) {
    fprintf(stderr, "Bucket less then 1\n");
    abort();
  }
  
  buckets = (struct bucket_t *)calloc(count, sizeof(struct bucket_t));

  for (int i = 0; i < count; i++) {
    add_left = (i == 0) ? 0: 1;
    buckets[i].min = i * bucket_size + add_left;
    buckets[i].max = (i == count - 1) ? max : (i + 1) * bucket_size;
  }

  for (int i = 0; i < count; i++) {
    for (int bi = 0; bi < count; bi++) {
      if (buckets[bi].min <= inp[i] && inp[i] <= buckets[bi].max) {
        add_to_bucket(&buckets[bi], inp[i]);
        break;
      }
    }
  }
 
  print_buckets(buckets, count);
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
