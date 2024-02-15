#include "cycle.h"

#include "list.h"
#include "permut.h"

#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

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
