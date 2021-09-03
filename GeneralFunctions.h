#ifndef GeneralFunctions_h
#define GeneralFunctions_h
#define _CRT_SECURE_NO_WARNINGS

/* This header file contains all of the project's essential libraries and functions*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <math.h>
#include "Structs.h"
#include "WinningPlayersFunctions.h"
#include "BoardFunctions.h"
#include "ActivePlayersFunctions.h"

/* A memory allocation checker function */
void checkAlloc(void* ptr);
/*checks if a list is empty*/
bool isEmptyList(List* lst);
/*resets a list*/
void makeEmptyList(List* lst);
/*creates a new node and calls insertNodeToEndList/*/
void insertDataToEndDList(List* dlst, int xCoord,int yCoord);
/*adds a node to end of a list and adjusts the head/tail*/
void insertNodeToEndDList(List* dlst, ListNode* newTail);
#endif /* GeneralFunctions_h */