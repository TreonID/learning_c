#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

#include "cycle.h"
#include "list.h"
#include "mask.h"
#include "permut.h"

struct form_t *GLOBAL_FORM;
struct node_t *GLOBAL_LIST_RESULT;

int main() {
    int *arr;
    int arr_size;
    struct form_t form;
    struct node_t *list;

    form.edges = 3;
    arr_size = form.edges * 2;
    arr = calloc(arr_size, sizeof(int));
    for (int i = 0; i < arr_size; ++i)
        arr[i] = i + 1;
    form.masks = calloc(form.edges, sizeof(struct mask_t));
    assign_mask(&form);
    GLOBAL_FORM = &form;

    generate(arr_size, arr, arr_size);

    list = GLOBAL_LIST_RESULT;
    for (int i = 0; i < list_len(list); ++i) {
        form_print(form, list_at_index(list, i)->data, arr_size);
    }

    free(form.masks);
    list_free(list);
    free(arr);
}