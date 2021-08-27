#ifndef GeneralFunctions_h
#define GeneralFunctions_h
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <math.h>
#include "Structs.h"

/* A memory allocation checker function */
void checkAlloc(void* ptr);

bool isEmptyList(List* lst);

void makeEmptyList(List* lst);
#endif /* GeneralFunctions_h */