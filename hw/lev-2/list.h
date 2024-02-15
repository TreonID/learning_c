#ifndef LIST_H
#define LIST_H

struct node_t {
    struct node_t *next;
    int *data;
};

struct node_t *make_node(int *data, int size);
void free_node(struct node_t *node);

struct node_t *list_append(struct node_t *list, int *data, int size);
void list_free(struct node_t *list);
int list_len(struct node_t *list);
struct node_t *list_copy(struct node_t *list, int size);
void list_arr_print(int *a, int size);
void list_print(struct node_t *list, int data_size);
struct node_t *list_at_index(struct node_t *list, unsigned index);

struct node_t *list_reverse(struct node_t *list);

int *arr_copy(int *a, int size);
int arr_comp_is_a_gt_b(int *a, int *b, int size);
void arr_copy_from_b_to_a(int *a, int *b, int size);

#endif