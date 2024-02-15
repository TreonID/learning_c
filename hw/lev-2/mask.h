#ifndef MASK_H
#define MASK_H

struct mask_t {
    unsigned pos[3];
};

struct form_t {
    int edges;
    struct mask_t *masks;
};

int mask_sum(struct mask_t mask, int *a, int size);
void mask_print(struct mask_t mask, int *a, int size);
void form_print(struct form_t form, int *a, int size);
void mask_print_value(struct form_t form);
void assign_mask(struct form_t *form);
int *masked_arr(struct form_t form, int *arr, int size);
int *unmasked_arr(struct form_t form, int *arr, int size);

extern const int MASK_LEN;

#endif