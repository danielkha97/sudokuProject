#ifndef BoardFunctions_h
#define BoardFunctions_h
#include "GeneralFunctions.h"



#define EMPTY_CELL -1
#define SIZE 9
#define SPACE ' '
#define NOT_FINISH 1
#define FINISH_SUCCESS 0
#define FINISH_FAILURE -1
#define FILLED 0
#define FAIL -1
#define NOT_FOUND -1


/* This function receives a sudoku board and returns a matrix of pointers to struct "Array" where every cell
 * contain the possible digits for every cell in the original board */
Array*** PossibleDigits(short sudokuBoard[][9]);

/* This functions builds the possibilities matrix from the given sudoku board */
Array*** initPossibilitiesMatrix(short sudokuBoard[][9]);

/* This function receives an empty cell and fills the possible number for this cell */
void fillPossibilities(Array* res, short sudokuBoard[][9], int row, int col);

/* This functions checks if every number from 1-9 if each is a possibility for the current cell */
bool isValidNum(short num, short sudokuBoard[][9], int row, int col);

/* This function fills in the locations with only 1 option */
int OneStage(short board[][9], Array*** possibilities, int* x, int* y);
bool checkAndFill(short board[][9], Array*** possibilities, int row, int col, int arrInd);

/* this is the sudoku board printing function */
void sudokoPrintBoard(short sudokuBoard[][9]);

/* this function supervises the functions from questions A,B*/
int FillBoard(short board[][9], Array*** possibilities);

/* This function asks the user which digit to choose in a cell to put in and fills it in the suddoku board and possibilities matrix accordingly*/
bool fillUserChoice(short board[][9], Array*** possibilities, int xCoord, int yCoord);

/*this function is a binary search function for finding the index of the item given in an array*/
int findIndInArray(short* arr, unsigned short size, int item);

/* this function updates the possibilities matrix after filling a one option digi-cell*/
void updatePossibilitiesMatrix(short board[][9], Array*** possibilities, int row, int col, int num, bool* isDuplicate);

/* this functions checks if deuplicates exist after filling the board with a 'single' */
void duplicatecheck(Array*** possibilities, int xCord, int yCord, int num, bool* isDuplicate);

/* this function frees the possibilities board*/
void freePossibilitiesBoard(Array*** possibilities);

/* creates a node of a list */
ListNode* nodeCreation(int XCoord, int YCoord, ListNode* prev, ListNode* next);

/* creating a list representing coordinates of a sudoku board */
List* boardListCreation();

/* this funtions updates a random value in a given coordinates */
void updateBoardRandomly(int XCoord, int YCoord, short board[][SIZE]);

/* this function removes a list node from a given list */
void removeFromList(List* list, ListNode* node);

/* this function creates randomize a game board and return a pointer to it */
short** randBoardCreation(List* boardList);

/* this functions counts the number of full cells in a board */
int countBoardFullCells(short** board);

#endif /* BoardFunctions_h */