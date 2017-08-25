#include <stdio.h>
#include "skel.h"

int get_count(d_list *head)
{
    int count = 0;
    d_list *current = head;
    while (current != NULL)
    {
	count++;
	current = current -> next;
    }
    return count;
}

