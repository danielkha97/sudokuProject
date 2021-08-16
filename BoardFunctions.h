#ifndef BoardFunctions_h
#define BoardFunctions_h
#include "GeneralFunctions.h"
#include "Structs.h"

#define EMPTY_CELL -1
#define SIZE 9
#define SPACE ' '

/* This function receives a sudoku board and returns a matrix of pointers to struct "Array" where every cell
 * contain the possible digits for every cell in the original board */
Array ***PossibleDigits(short sudokuBoard[][9]);

/* This functions builds the possibilities matrix from the given sudoku board */
Array ***initPossibilitiesMatrix(short sudokuBoard[][9]);

/* This function receives an empty cell and fills the possible number for this cell */
void fillPossibilities(Array *res, short sudokuBoard[][9], int row, int col);

/* This functions checks if every number from 1-9 if each is a possibility for the current cell */
bool isValidNum(short num, short sudokuBoard[][9], int row, int col);

/* This function fills in the locations with only 1 option */
int OneStage(short board[][9], Array*** possibilities, int* x, int* y);
void checkAndFill(short board[][9], Array*** possibilities, int row, int col);

/* this is the sudoku board printing function */
void sudokoPrintBoard(short sudokuBoard[][9]);


#endif /* BoardFunctions_h */