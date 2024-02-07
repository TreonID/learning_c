#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#include "my_list.h"

int num_from_list(struct node_t *list);

int is_prime(int x) {
  if (x < 2) return 1;
  for (int i = 2; i * i <= x; ++i) 
    if ((x % i) == 0)
      return 0;
  return 1; 
}

int is_prime_rev(int x) {
    return (is_prime(x) == 0) ? 1 : 0;
}


void permut(struct node_t *list, int l, int r, int *check_not_prime) {
    int i;
    if (l == r) {
        list_print(list);
        *check_not_prime = (*check_not_prime == 1) ? 1 : is_prime_rev(num_from_list(list));
        printf("Int: %d ip: %d Check: %d\n", num_from_list(list),  is_prime_rev(num_from_list(list)), *check_not_prime);
    } else {
        for (i = l; i <= r; i++) {
            list_swap(list, l, i);
            permut(list, l + 1, r, check_not_prime);
            list_swap(list, l, i);
        }
    }
}

struct node_t *list_from_num(int num) {
    struct node_t *top = make_node(num % 10);
    num = num / 10;
    while (num > 0) {
        list_append(top, num % 10);
        num = num / 10;
    }
    return list_reverse(top);
}

int num_from_list(struct node_t *list) {
    struct node_t *tmp_list = list_reverse(list_copy(list));
    int result = 0;
    int mult = 1;
    for (int i = 0; i < list_len(tmp_list); i++) {
        if (i > 0) mult = mult * 10;
        result += mult * list_at_index(tmp_list, i)->data;
    }
    list_free(tmp_list);
    return result;
}

int main() {
    int n = 0;
    int x = 131;
    int check_not_prime = 0;
    struct node_t *list = list_from_num(x);
    n = list_len(list);
    permut(list, 0, n - 1, &check_not_prime);
    if (check_not_prime == 0) {
        printf("%d is permutation prime\n", x);
    }
    list_free(list);
}