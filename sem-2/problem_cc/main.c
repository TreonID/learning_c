#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#include "my_list.h"

#if 0
void permute(char *a, int l, int r) {
    int i;
    if (l == r)
        printf("%s\n", a);
    else {
        for (i = l; i <= r; i++) {
            swap((a + l), (a + i));
            permute(a, l + 1, r);
            swap((a + l), (a + i));
        }
    }
}


#endif
void permute(struct node_t * list, int l, int r) {
    int i;
    if (l == r)
        list_print(list);
    else {
        for (i = l; i <= r; i++) {
            list_swap(list, l, i);
            permute(list, l + 1, r);
            list_swap(list, l, i);
        }
    }
}


int main() {
#if 0
    char str[] = "ABC";
    int n = strlen(str);
    permute(str, 0, n - 1);
#endif
    int n = 0;
    struct node_t *list = make_node(9);
    list_append(list, 7);
    list_append(list, 1);
    n = list_len(list);
    permute(list, 0, n - 1);
}