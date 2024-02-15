#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

#include "list.h"
#include "mask.h"

void swap(int *a, int *b);
void generate(int k, int *a, int size);
void output(int *a, int size);

void cycle_move(int *arr, int size, int step);
int arr_val_equal(int *a1, int *a2, int size);
int cycle_move_count(int size, int step);

struct form_t *GLOBAL_FORM;
struct node_t *GLOBAL_LIST_RESULT;

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
            }
            if (add_flag)
                list_append(list, a, size);
        }
        free(tmp);
    }
}

void cycle_move(int *arr, int size, int step) {
    int *tmp = calloc(size, sizeof(int));
    for (int i = 0; i < size - step; ++i)
        tmp[i + step] = arr[i];
    for (int i = size - step; i < size; ++i)
        tmp[i - (size - step)] = arr[i];

    for (int i = 0; i < size; ++i)
        arr[i] = tmp[i];

    free(tmp);
}

int arr_val_equal(int *a1, int *a2, int size) {
    int res = 1;
    for (int i = 0; i < size; ++i)
        if (a1[i] != a2[i]) res = 0;
    return res;
}

int cycle_move_count(int size, int step) { return size / step; }

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