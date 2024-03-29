//---------------------------------------------
// 
// Builds a mask for arrays according to a triangle, square, etc. pattern. 
// Contains functions for calculating the sum, displaying it, converting to linear form and vice versa.
// 
//  1. mask_sum - calc sum of one line, by struct mask_t { unsigned pos[3]; };
//  2. mask_print - print array values of one line, by struct mask_t { unsigned pos[3]; };
//  3. form_print - print array values of all lines, struct form_t { int edges; struct mask_t *masks; };
//  4. mask_print_value - pint mask values, used for debug
//  5. assign_mask - build struct form_t. Example: {1, 2, 3} {4, 3, 5} {6, 5, 2}
//     last elem of k = second elem of k+1
//     last elem of last k = second elem of k0
//  6. 4,3,2; 6,2,1; 5,1,3; -> masked_arr -> {4, 3, 2, 6, 2, 1, 5, 1, 3}
//  7. {4, 3, 2, 6, 2, 1, 5, 1, 3} -> unmasked_arr ->  4,3,2; 6,2,1; 5,1,3;
//
//---------------------------------------------

#include "mask.h"

#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

const int MASK_LEN = 3;

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

int *unmasked_arr(struct form_t form, int *arr, int size) {
    int *res;
    res = calloc(MASK_LEN * form.edges, sizeof(int));
    for (int m = 0; m < form.edges; ++m)
        for (int p = 0; p < MASK_LEN; ++p)
            // res[m * MASK_LEN + p] = arr[form.masks[m].pos[p]];
            res[form.masks[m].pos[p]] = arr[m * MASK_LEN + p];
    return res;
}
