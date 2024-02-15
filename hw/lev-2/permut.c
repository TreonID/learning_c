#include "permut.h"

#include "cycle.h"
#include "list.h"
#include "mask.h"

#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void generate(int k, int *a, int size) {
    // Heap's algorithm
    if (k == 1)
        output(a, size);
    else {
        // less swap
        generate(k - 1, a, size);

        for (int i = 0; i < k - 1; ++i) {
            if (k % 2 == 1)
                swap(&a[0], &a[k - 1]);
            else
                swap(&a[i], &a[k - 1]);

            generate(k - 1, a, size);
        }
    }
}

void output(int *a, int size) {
    struct form_t form = *GLOBAL_FORM;
    struct node_t *list = GLOBAL_LIST_RESULT;
    int *tmp, *lst_tmp, l_len, add_flag;

    int sum = mask_sum(form.masks[0], a, size);
    int sum_equal_flag = 1;
    for (int i = 1; i < form.edges; ++i)
        if (mask_sum(form.masks[i], a, size) != sum)
            sum_equal_flag = 0;

    if (sum_equal_flag) {
        tmp = masked_arr(form, a, size);
        l_len = list_len(list);

        if (l_len == 0) {
            list = make_node(a, size);
            GLOBAL_LIST_RESULT = list;
        } else {
            add_flag = 1;
            for (int l = 0; l < l_len; ++l) {
                lst_tmp = masked_arr(form, list_at_index(list, l)->data, size);
                for (int cc = 0; cc < cycle_move_count(form.edges * MASK_LEN, MASK_LEN); ++cc) {
                    if (arr_val_equal(tmp, lst_tmp, size))
                        add_flag = 0;
                    cycle_move(tmp, form.edges * MASK_LEN, MASK_LEN);
                }
                free(lst_tmp);
            }
            if (add_flag)
                list_append(list, a, size);
        }
        free(tmp);
    }
}
