// 
// Heap's algorithm for enumerating options, processing results
//

#ifndef PERMUT_H
#define PERMUT_H

void swap(int *a, int *b);
void generate(int k, int *a, int size);
void output(int *a, int size);

extern struct form_t *GLOBAL_FORM;
extern struct node_t *GLOBAL_LIST_RESULT;

#endif