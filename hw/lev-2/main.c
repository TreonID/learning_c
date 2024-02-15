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

int SWAP_COUNTER = 0;
int PERMUT_COUNTER = 0;

struct form_t *GLOBAL_FORM;

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

    int sum = mask_sum(form.masks[0], a, size);
    int sum_equal_flag = 1;
    for (int i = 1; i < form.edges; ++i)
        if (mask_sum(form.masks[i], a, size) != sum)
            sum_equal_flag = 0;

    if (sum_equal_flag) {
        form_print(form, a, size);
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

    for (int i = 0; i < form->edges; ++i) {
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
    }
    form->masks[form->edges-1].pos[MASK_LEN-1] = form->masks[0].pos[1];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int arr_size = 6;
    struct form_t form;
    struct node_t *list = make_node(arr, arr_size);
    list_append(list, arr, arr_size);

    list_print(list, arr_size);

    form.edges = 3;
    form.masks = calloc(form.edges, sizeof(struct mask_t));

    assign_mask(&form);
    mask_print_value(form);

    GLOBAL_FORM = &form;

    // generate(arr_size, arr, arr_size);
    // printf("Swap: %d Permut: %d\n", SWAP_COUNTER, PERMUT_COUNTER);

    free(form.masks);
    list_free(list);
}