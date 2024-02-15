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

void run_form_calc(int edges) {
    int *arr;
    int arr_size;
    struct form_t form;
    struct node_t *list;
    int unmasked_len;
    int *tmp, *tmp_store, *tmp_print;

    form.edges = edges;
    arr_size = form.edges * 2;
    arr = calloc(arr_size, sizeof(int));
    for (int i = 0; i < arr_size; ++i)
        arr[i] = i + 1;
    form.masks = calloc(form.edges, sizeof(struct mask_t));
    assign_mask(&form);
    GLOBAL_FORM = &form;

    generate(arr_size, arr, arr_size);
    list = GLOBAL_LIST_RESULT;

    unmasked_len = form.edges * MASK_LEN;

    for (int i = 0; i < list_len(list); ++i) {
        // Sort cycle moves
        tmp = masked_arr(form, list_at_index(list, i)->data, arr_size);
        tmp_store = arr_copy(tmp, unmasked_len);
        for (int cc = 0; cc < cycle_move_count(unmasked_len, MASK_LEN); ++cc) {
            cycle_move(tmp, unmasked_len, MASK_LEN);
            if (arr_comp_is_a_gt_b(tmp_store, tmp, unmasked_len))
                arr_copy_from_b_to_a(tmp_store, tmp, unmasked_len);
        }
        tmp_print = unmasked_arr(form, tmp_store, arr_size);
        form_print(form, tmp_print, arr_size);

        free(tmp);
        free(tmp_store);
        free(tmp_print);
    }

    free(form.masks);
    list_free(list);
    free(arr);
}

int main() {
    // 3 - magic triangle; 4 - magic square; ...
    run_form_calc(3);
}