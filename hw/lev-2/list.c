#include "list.h"

#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

struct node_t *make_node(int *data, int size) {
    struct node_t *node = calloc(1, sizeof(struct node_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error");
        abort();
    }
    node->data = arr_copy(data, size);
    return node;
}

void free_node(struct node_t *node) {
    free(node->data);
    free(node);
}

struct node_t *list_append(struct node_t *list, int *data, int size) {
    struct node_t *node = list;
    struct node_t *new_node = make_node(data, size);
    while (node->next != NULL)
        node = node->next;
    node->next = new_node;
    return new_node;
}

void list_free(struct node_t *list) {
    struct node_t *node = list;
    struct node_t *del_node = list;
    if (list == NULL) return;
    while (node->next != NULL) {
        del_node = node;
        node = node->next;
        free_node(del_node);
    }
    free_node(node);
}

int list_len(struct node_t *list) {
    struct node_t *node = list;
    if (list == NULL) return 0;
    int len = 1;
    while (node->next != NULL) {
        node = node->next;
        ++len;
    }
    return len;
}

struct node_t *list_copy(struct node_t *list, int size) {
    struct node_t *top;
    struct node_t *node = list;
    if (list == NULL) return NULL;
    top = make_node(node->data, size);
    while (node->next != NULL) {
        node = node->next;
        list_append(top, node->data, size);
    }
    return top;
}

void list_arr_print(int *a, int size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        if (i != size - 1)
            printf("%d, ", a[i]);
        else
            printf("%d", a[i]);
    }
    printf("]");
}


void list_print(struct node_t *list, int data_size) {
    struct node_t *node = list;
    if (list == NULL) {
        printf("List: (NULL)\n");
        return;
    }
    printf("List: (\n\t");
    list_arr_print(node->data, data_size);
    while (node->next != NULL) {
        printf(", \n\t");
        node = node->next;
        
        list_arr_print(node->data, data_size);
    }
    printf("\n)\n");
}

struct node_t *list_at_index(struct node_t *list, unsigned index) {
    struct node_t *node = list;
    int i = 0;
    if (list == NULL) return NULL;
    if (index == 0) return list;
    while (node->next != NULL) {
        node = node->next;
        ++i;
        if (i == index) return node;
    }
    fprintf(stderr, "Error: index out of list range\n");
    abort();
}

struct node_t *list_reverse(struct node_t *list) {
    struct node_t *first = NULL, *second = NULL, *tmp;
    if (list == NULL) return NULL;
    if (list->next == NULL) return list;
    first = list;
    second = list->next;
    list->next = NULL;
    while (second != NULL) {
        tmp = second->next;
        second->next = first;
        first = second;
        second = tmp;
    }
    return first;
}

int *arr_copy(int *a, int size) {
    int *new = calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) new[i] = a[i];
    return new;
}
