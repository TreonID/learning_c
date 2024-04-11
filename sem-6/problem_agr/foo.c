#include <stdio.h>

int foo(int *arr, int start, int last) {
    int acc = 0, k = arr[start];
    if (start >= last) return last;
    for (int i = start + 1; i <= last; i++) {
        if (arr[i] <= k)
            acc++;
    }
    return acc;
}


int main() {
    int arr1[] = {5, 6, 8, 4, 5, 6, 3, 8, 1, 2};
    int arr3[] = {1, 1, 2, 3, 3, 3, 5, 5, 9, 9};
    int last = 9;
    printf("%d\n", foo(arr1, 0, last));
    printf("%d\n", foo(arr3, 0, last));
}