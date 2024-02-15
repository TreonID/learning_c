#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

#include "list.h"

const int MASK_LEN = 3;

struct mask_t {
    unsigned pos[3];
};

struct form_t {
    int edges;
    struct mask_t *masks;
};

void swap(int *a, int *b);
void generate(int k, int *a, int size);
void output(int *a, int size);

void arr_print(int *a, int size);

int mask_sum(struct mask_t mask, int *a, int size);
void mask_print(struct mask_t mask, int *a, int size);
void form_print(struct form_t form, int *a, int size);

int *masked_arr(struct form_t form, int *arr, int size);
void cycle_move(int *arr, int size, int step);
int arr_val_equal(int *a1, int *a2, int size);
int cycle_move_count(int size, int step);

int SWAP_COUNTER = 0;
int PERMUT_COUNTER = 0;

struct form_t *GLOBAL_FORM;
struct node_t *GLOBAL_LIST_RESULT;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    SWAP_COUNTER++;
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
    PERMUT_COUNTER++;
}

void arr_print(int *a, int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        if (i != size - 1)
            printf("%d, ", a[i]);
        else
            printf("%d", a[i]);
    }
    printf("]");
}

int mask_sum(struct mask_t mask, int *a, int size) {
    int acc = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < MASK_LEN; ++j) {
            if (mask.pos[j] == i)
                acc += a[i];
        }
    }
    return acc;
}

void mask_print(struct mask_t mask, int *a, int size) {
    for (int i = 0; i < MASK_LEN; ++i) {
        printf("%d", a[mask.pos[i]]);
        if (i < MASK_LEN - 1)
            printf(",");
    }
    printf("; ");
}

void form_print(struct form_t form, int *a, int size) {
    for (int i = 0; i < form.edges; ++i)
        mask_print(form.masks[i], a, size);
    printf("\n");
}

void mask_print_value(struct form_t form) {
    printf("MASK: ");
    for (int i = 0; i < form.edges; ++i) {
        for (int j = 0; j < MASK_LEN; ++j) {
            if (j == MASK_LEN - 1)
                printf("%d; ", form.masks[i].pos[j]);
            else
                printf("%d,", form.masks[i].pos[j]);
        }
    }
    printf("\n");
};

void assign_mask(struct form_t *form) {
    // last elem of k = second elem of k+1
    // last elem of last k = second elem of k0
    int last_assign = -1;
    int last_end_elem = -1;

    for (int i = 0; i < form->edges; ++i)
        for (int j = 0; j < MASK_LEN; ++j) {
            if (j == 1) {
                if (last_end_elem == -1) {
                    last_assign += 1;
                    form->masks[i].pos[j] = last_assign;
                } else {
                    form->masks[i].pos[j] = last_end_elem;
                }
            } else {
                last_assign += 1;
                form->masks[i].pos[j] = last_assign;
                if (j == MASK_LEN - 1) last_end_elem = last_assign;
            }
        }
    form->masks[form->edges - 1].pos[MASK_LEN - 1] = form->masks[0].pos[1];
}

int *masked_arr(struct form_t form, int *arr, int size) {
    int *res;
    res = calloc(MASK_LEN * form.edges, sizeof(int));
    for (int m = 0; m < form.edges; ++m)
        for (int p = 0; p < MASK_LEN; ++p)
            res[m * MASK_LEN + p] = arr[form.masks[m].pos[p]];
    return res;
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