#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *add_to_list_start(struct node_t *list, struct node_t *element) {
  element->next = (list) ? list : NULL;
  return element;
}

struct node_t *add_to_list_end(struct node_t *list, struct node_t *element) {
  struct node_t *top;
  if (list) {
    top = list;
    for (; ; ) {
      if (!list->next) {
        list->next = element;
        break;
      }
      list = list->next;
    }
    return top;
  }
  return element;
}

struct node_t *read_list(FILE *inp) {
  struct node_t *element = NULL;
  struct node_t *list_even = NULL;
  struct node_t *list_odd = NULL;

  for (; ; ) {
    int res, n;
    res = fscanf(inp, "%d", &n);
    if (res == EOF) {
      break;
    }
    if (res != 1) {
      fprintf(stderr, "File have broken format\n");
      fclose(inp);
      abort();
    }

    element = (struct node_t *)calloc(1, sizeof(struct node_t));
    element->data = n;

    if (n % 2 == 0) {
      list_even = add_to_list_end(list_even, element);
    } else {
      list_odd = add_to_list_end(list_odd, element);
    }
  }

  return add_to_list_end(list_even, list_odd);
}

void delete_list(struct node_t *top) {
  struct node_t *next;

  if (top) {
    for (; ; ) {
      if (!top->next) {
        free(top);
        break;
      }
      next = top->next;
      free(top);
      top = next;
    }
  }
}

void print_list(const struct node_t *list) {
  if (list) {
    for (; ; ) {
      if (!list->next) {
        printf("%d\n", list->data);
        break;
      }
      printf("%d->", list->data);
      list = list->next;
    }
  } else {
    printf("List is null\n");
  }
}

int main(int argc, char **argv) {
  FILE *f;
  struct node_t *list;

  if (argc < 2) {
    fprintf(stderr, "Example: %s test_file_name\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");

  if (!f) {
    perror("Error opening file");
    return 1;
  }

  list = read_list(f);
  print_list(list);
  delete_list(list);

  fclose(f);
}
