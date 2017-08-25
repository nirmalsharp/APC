#include <stdio.h>
#ifndef SKEL_H
#define SKEL_H
#define SUCCESS 1
#define FAILURE 0

typedef int data_t;
/*this is the structure of linked list*/
typedef struct linkedlist
{
    int data;
    struct linkedlist *prev;
    struct linkedlist *next;
}d_list;

void seperate(char *buffer, d_list **expA, d_list **expB, d_list **result);
int insert_first(d_list **head, d_list **tail, data_t num);
int insert_last(d_list **head, d_list **tail, data_t num);
void print_list(d_list **head, d_list **tail);
d_list *create_node(data_t num);
int delete_first(d_list **head, d_list **tail);
int delete_last(d_list **head, d_list **tail);
void delete_list(d_list **head);
d_list *sum(d_list **expA, d_list **evaB, d_list **result, d_list **tailA, d_list **tailB, d_list **tailC);
void print_res(d_list **head, d_list **tail, int length);
void subtract(d_list **expA, d_list **evaB, d_list **result, d_list **tailA, d_list **tailB, d_list **tailC);
void multiply(d_list **expA, d_list **evaB, d_list **result, d_list **tailA, d_list **tailB, d_list **tailC);
d_list *new_sum(d_list **expA, d_list **evaB, d_list **tailB, d_list **tailD);
void insert_l(d_list **head, int num);
void insert_f(d_list **head, int num);
int get_count(d_list *head);
#endif
