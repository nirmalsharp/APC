#include <stdio.h>
#include <stdlib.h>
#include "skel.h"

/*this is the create node */
d_list* create_node(data_t data)
{
    d_list *new = malloc(sizeof(d_list));
    new -> data = data;
    new -> next = NULL;
    new -> prev = NULL;
    return new;
}




void insert_f(d_list **head, int num)
{
    d_list *ptr = *head;

    if (*head == NULL)
    {
	*head = create_node(num);
    }

    else

    {
	d_list *new = create_node(num);
	new -> next = *head;
	*head = new;
	new -> prev = NULL;

	if (ptr != NULL)
	{
	    ptr -> prev = *head;
	}


    }

}




void insert_l(d_list **head, int num)
{

    if (*head == NULL)
    {
	*head = create_node(num);
    }

    else
    {

	d_list *ptr = *head;
	d_list *last =  *head;

	while (ptr != NULL)
	{
	    last = ptr;
	    ptr = ptr -> next;
	}
	d_list *new  = create_node(num);
	last -> next = new;
	new -> next = NULL;
	new -> prev = last;



    }



}




/****this is functions file*****/
int insert_last(d_list **head, d_list **tail, data_t data)
{
    d_list *new = create_node(data);

    /*check if the node is created*/
    if (new == NULL)
    {
	return FAILURE;
    }

    /*if the list is empty*/
    if (*head == NULL)
    {
	*head = *tail = new;
	return SUCCESS;	
    }

    /*if the list is not empty*/
    (*tail) -> next = new;
    new -> prev = *tail;
    *tail = new;
    return SUCCESS;
}


/*this function is about insert first*/
int insert_first(d_list **head, d_list **tail, data_t data)
{
    d_list *new = create_node(data);
    d_list *ptr = *head;

    /*check if the node is created*/
    if (new == NULL)
    {
	return FAILURE;
    }

    /*if the list is empty*/
    if (*head == NULL)
    {
	*head = *tail = new;
	return SUCCESS;
    }

    /*if the list is not empty*/
    //(*tail) -> next = *head;
    *tail = *head;
    new -> next = *head;
    new -> prev = NULL;
    *head  = new;
    if (ptr != NULL)
    {
	ptr -> prev = *head;
    }
    return SUCCESS;

}

/*this function is about delete last*/
int delete_last(d_list **head, d_list **tail)
{
    d_list *ptr = *head;
    d_list *ptr1 = *tail;

    /*if the list is empty*/
    if (*head == NULL)
    {
	printf("no items in the list\n");
	return FAILURE;
    }

    /*if the list is one*/
    if (ptr -> next == NULL)
    {
	free(*head);
	*head = NULL;
	return SUCCESS;
    }

    /*if the list is not empty*/
    *tail = (*tail) -> prev;
    free(ptr1);
    (*tail) -> next = NULL;


}

/*this function is about delete first*/
int delete_first(d_list **head, d_list **tail)
{
    d_list *ptr = *head;
     
    /*if the list is empty*/
    if (*head == NULL)
    {
	printf("no items in the list\n");
	return SUCCESS;
    }

    /*if the list is one*/
    if (ptr -> next == NULL)
    {
	free(*head);
	*head = NULL;
	*tail = NULL;
	return SUCCESS;
    }

    /*if the list is not empty*/
    *head = (*head) -> next;
    free(ptr);
    (*head) -> prev = NULL;

}

/*this function is about delete the list*/

void delete_list(d_list **head)
{
    d_list *ptr = *head;
    /*check the list is empty or not*/
    if (*head != NULL)
    {
	/*move the pointer*/

	while (ptr != NULL)

	{
	    ptr = ptr -> next;
	    free(ptr);
	}

	*head = NULL;
    }

    else
    {
	printf("NO LISTS AVAILABLE\n");
    }

}

/*this function is about delete element*/
int delete_element(d_list **head, d_list **tail, int element)
{
    d_list *ptr = *head;
    d_list *before = *head;
    d_list *after = *head;

    /*list is available or not*/
    if (*head == NULL)
    {
	printf("no lists available\n");
	return SUCCESS;
    }

    /*delete element*/
    while (ptr -> data != element)
    {
	ptr = ptr -> next;

	if (ptr == NULL)
	{
	    printf("no element found\n");
	    return SUCCESS;
	}
    }
    /*check the condition*/
    if (ptr == *head)
    {
	delete_first(head, tail);
    }
    else if (ptr -> next != NULL)
    {

	before  = ptr -> prev;
	before -> next = ptr -> next;
	after = ptr -> next;
	after -> prev = before;
	free(ptr);
    }
    else
    {

	delete_last(head, tail);

    }


}

/*this function is about insert after*/
int insert_after(d_list **head, d_list **tail, int search, int element)
{

    /*take pointer and storing value*/
    d_list *ptr  = *head;

    if (*head == NULL)
    {
	printf("no lists available\n");
	return FAILURE;
    }

    /*traverse the list*/

    while (ptr -> data != element)
    {
	ptr = ptr -> next;
	/**element not found**/
	if (ptr == NULL)
	{
	    printf("no element found\n");
	    return FAILURE;
	}
    }

    if (ptr -> next == NULL)
    {
	insert_last(head, tail, search);
	return SUCCESS;
    }

    d_list *new = create_node(search);
    new -> next = ptr -> next;
    new -> prev = ptr;
    ptr -> next = new;
}


/*this function is about insert `before*/

int insert_before(d_list **head, d_list **tail, int search, int element)
{
    d_list *ptr = *head;
    d_list *ptr1 = *head;

    /*check list*/
    if (*head == NULL)
    {	         printf("no lists available\n");
	return;
    }

    /*traversing the list*/
    while (ptr -> data != element)
    {
	ptr1 = ptr;
	ptr = ptr -> next;
	/*element not found*/
	if (ptr == NULL)
	{
	    printf("search element not found\n");
	    return SUCCESS;
	}

    }
    if (ptr -> prev != NULL)
    {
	d_list *new = create_node(search);

	ptr1 -> next = new;
	new -> next = ptr;
	new -> prev = ptr -> prev;
	ptr -> prev = new;
    }

    else
    {

	insert_first(head, tail, search);

    }		 
}


/*this function is about print list*/
void print_list(d_list **head, d_list **tail)

{

    /*something inside the list*/
    if (*head != NULL)
    {
	d_list *ptr = *head;

	while (ptr  != NULL)
	{
	    printf("%d\n", ptr -> data);
	    ptr = ptr -> next;
	}
    }

    /*function check no items*/
    else
    {
	printf("NO items in the list\n");
    }


}


    
