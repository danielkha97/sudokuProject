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

