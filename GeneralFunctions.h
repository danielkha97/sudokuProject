#ifndef GeneralFunctions_h
#define GeneralFunctions_h
#define _CRT_SECURE_NO_WARNINGS

/* This header files contains all of the project's essential libraries and functions*/

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

bool isEmptyList(List* lst);

void makeEmptyList(List* lst);

void insertDataToEndDList(List* dlst, int xCoord,int yCoord);

void insertNodeToEndDList(List* dlst, ListNode* newTail);
#endif /* GeneralFunctions_h */