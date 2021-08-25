#include <stdio.h>
#include "GeneralFunctions.h"

void checkAlloc (void* ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation failed!\nTerminating the program.\n");
        exit(1);
    }
}

bool isEmptyList(List* lst)
{
    return (lst->head == NULL);
}

void makeEmptyList(List* lst)
{
    lst->head = lst->tail = NULL;
}