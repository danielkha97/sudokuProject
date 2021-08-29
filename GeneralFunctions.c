
#include "GeneralFunctions.h"

void checkAlloc(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\nTerminating the program.\n");
		exit(1);
	}
}
//Coordinates list functions
bool isEmptyList(List* lst)
{
	return (lst->head == NULL);
}
void makeEmptyList(List* lst)
{
	lst->head = lst->tail = NULL;
}

void insertDataToEndDList(List* dlst, int xCoord, int yCoord)
{
	List* newTail;

	newTail = nodeCreation(xCoord, yCoord, NULL, NULL);
	insertNodeToEndDList(dlst, newTail);
}

void insertNodeToEndDList(List* dlst, ListNode* newTail)
{
	if (isEmptyList(dlst))
		dlst->head = dlst->tail = newTail;
	else
	{
		newTail -> prev = dlst->tail;
		newTail -> next = NULL;
		dlst -> tail -> next = newTail;
		dlst -> tail = newTail;
	}
}
