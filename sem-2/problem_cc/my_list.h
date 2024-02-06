#ifndef MY_LIST_H
#define MY_LIST_H

struct node_t {
    struct node_t *next;
    int data;
};

struct node_t *make_node(int data);
void free_node(struct node_t *node);

struct node_t *list_append(struct node_t *list, int data);
void list_free(struct node_t *list);
int list_len(struct node_t *list);
struct node_t *list_copy(struct node_t *list);
void list_print(struct node_t *list);
struct node_t *list_at_index(struct node_t *list, unsigned index);
void list_swap(struct node_t *list, unsigned index_a, unsigned index_b);

#endif
