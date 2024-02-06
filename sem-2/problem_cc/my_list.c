#include "my_list.h"

#ifndef STD_INC
#define STD_INC

#include <stdio.h>
#include <stdlib.h>

#endif

struct node_t *make_node(int data) {
    struct node_t *node = calloc(1, sizeof(struct node_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error");
        abort();
    }
    node->data = data;
    return node;
}

void free_node(struct node_t *node) {
    free(node);
}

struct node_t *list_append(struct node_t *list, int data) {
    struct node_t *node = list;
    struct node_t *new_node = make_node(data);
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

struct node_t *list_copy(struct node_t *list) {
    struct node_t *top;
    struct node_t *node = list;
    if (list == NULL) return NULL;
    top = make_node(node->data);
    while (node->next != NULL) {
        node = node->next;
        list_append(top, node->data);
    }
    return top;
}

void list_print(struct node_t *list) {
    struct node_t *node = list;
    if (list == NULL) {
        printf("List: (NULL)\n");
        return;
    }
    printf("List: (%d", node->data);
    while (node->next != NULL) {
        printf(", ");
        node = node->next;
        printf("%d", node->data);
    }
    printf(")\n");
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

void list_swap(struct node_t *list, unsigned index_a, unsigned index_b) {
    int temp = list_at_index(list, index_a)->data;
    list_at_index(list, index_a)->data = list_at_index(list, index_b)->data;
    list_at_index(list, index_b)->data = temp;
}
