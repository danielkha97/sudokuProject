
#include "BoardFunctions.h"



Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** res;
	res = initPossibilitiesMatrix(sudokuBoard);

	return res;

}


Array*** initPossibilitiesMatrix(short sudokuBoard[][9])
{
	Array*** res;
	int i, j;

	res = (Array***)malloc(SIZE * sizeof(Array**));
	checkAlloc(res);

	for (i = 0; i < SIZE; i++)
	{
		res[i] = (Array**)malloc(SIZE * sizeof(Array*));
		checkAlloc(res[i]);

		for (j = 0; j < SIZE; j++)
		{
			if (sudokuBoard[i][j] == EMPTY_CELL)
			{
				res[i][j] = (Array*)malloc(sizeof(Array));
				checkAlloc(res[i][j]);
				fillPossibilities(res[i][j], sudokuBoard, i, j);
			}
			else
				res[i][j] = NULL;

		}
	}

	return res;
}

void fillPossibilities(Array* res, short sudokuBoard[][9], int row, int col)
{

	short num;
	int logSize = 0;

	res->arr = (short*)malloc(SIZE * sizeof(short));
	checkAlloc(res->arr);

	for (num = 1; num <= SIZE; num++)
	{
		if (isValidNum(num, sudokuBoard, row, col))
		{
			(res->arr)[logSize] = num;
			logSize++;
		}
	}

	if (logSize < SIZE)
	{
		res->arr = (short*)realloc(res->arr, logSize * sizeof(short));
		checkAlloc(res->arr);
	}

	res->size = logSize;

}

/* This functions checks if the argument "num" given is a possibility for the current cell */
bool isValidNum(short num, short sudokuBoard[][9], int row, int col)
{
	bool flag = true;
	int i, xCoord, yCoord;

	for (i = 0; i < SIZE && flag; i++) // checks row and col of the current cell
	{
		if (sudokuBoard[row][i] == num || sudokuBoard[i][col] == num)
			flag = false;

	}

	if (flag) // if true, checks the entire cube of the current cell
	{
		xCoord = row - (row % 3); // Retrieves y  for the current cube that we're gonna check
		yCoord = col - (col % 3); // Retrieves x and y starting values for the current cube that we're gonna check

		for (i = 0; i < 3 && flag; i++)
		{
			if (sudokuBoard[xCoord + i][yCoord] == num || sudokuBoard[xCoord + i][yCoord + 1] == num || sudokuBoard[xCoord + i][yCoord + 2] == num)
				flag = false;
		}
	}

	return flag;
}
/* This function fills in the locations with only 1 option */
int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
	int singles = 0, emptyCells = 0, minLength = 9, res = 0;
	bool areSingles = true;/* the flag is true as long as there are single option cells to fill - when there aren't the while loop will stop and the correct case is returned */

	while (areSingles == true)
	{
		if (singles == 0)
			areSingles = false;

		for (int i = 0; i < SIZE && res != FINISH_FAILURE; i++)
		{
			for (int j = 0; j < SIZE && res != FINISH_FAILURE ; j++)
			{
				/* step 1 - checking each cell for length of possibilities array */

				/* here we check the possibilities array isn't empty and lentgh equals to 1 (for 1 cell in the mat) */
				if (possibilities[i][j] != NULL && possibilities[i][j]->size == 1)				
                {
					areSingles = true; /* since there's a single cell, the board will be updated and the loop needs to repeat once more */
					singles++;
					emptyCells++;
					if (checkAndFill(board, possibilities, i, j))
					{
						singles--;
						emptyCells--;
					}
					else
					{
						/* the board is illegal - returning failure and terminating the loop */
						areSingles = false;
						x = NULL;
						y = NULL;
						res = FINISH_FAILURE;
						break;
					}


				}
				/* if the cell is empty & more than one possibility, checking if it's the shortest possibilities array */
				if (possibilities[i][j] != NULL && possibilities[i][j]->size > 1)
				{
					emptyCells++;
					/* checking if this cell has the shortest array of posibilities to fill */
					if (possibilities[i][j]->size < minLength)
					{
						*x = i;
						*y = j;

						/* replacing the shortest length */
						minLength = possibilities[i][j]->size;
					}
				}
			}
		}

		if (areSingles)
			possibilities = PossibleDigits(board); /* we update the possibilities board is there were changes to the board */

		/* now checking if the board was filled entirely */
		if (emptyCells == 0)
		{
			x = NULL;
			y = NULL;
			res = FINISH_SUCCESS;
			areSingles = false;
		}

		else
		{
            res = NOT_FINISH;
			areSingles = false;
		}
	}

	return res;
	
}
bool checkAndFill(short board[][9], Array*** possibilities, int row, int col)
{
	/* isValidNum checks if the number is a legal option at a given location - returns true if legal*/
	if (isValidNum(possibilities[row][col]->arr[0], board, row, col))
	{
		/*setting the value in the game board */
		board[row][col] = possibilities[row][col]->arr[0];

		/* freeing the cell in possibilities board */
		free(possibilities[row][col]->arr);
		free(possibilities[row][col]);
		return true;
	}
	else
		return false;
}

void sudokoPrintBoard(short sudokuBoard[][9])
{
	int i, j, k;

	for (i = -1; i < SIZE; i++)
	{
		if (i == -1)
		{
			printf("  ");
			for (j = 0; j < SIZE; j++)
			{
				if (j == j - (j % 3))
					printf(" |");
				printf("  %d ", j);
			}
			printf("\n");
		}

		else
		{
			if (i % 3 == 0) /* meaning rows 0 or 3 or 6 */
			{
				printf(" ");
				for (k = 0; k < 6; k++)
				{
					printf("-------");
				}

				printf("--\n ");

				printf("%d |", i);

				for (k = 0; k < SIZE; k++)
				{
					if (sudokuBoard[i][k] != EMPTY_CELL)
					{
						if ((k == k - (k % 3)) && k != 0)
							printf(" |");
						printf("  %d ", sudokuBoard[i][k]);
					}

					else
					{
						if ((k == k - (k % 3)) && k != 0)
							printf(" |");
						printf("  %c ", SPACE);
					}
				}

				printf("\n");

			}

			else
			{

				printf(" %d |", i);

				for (k = 0; k < SIZE; k++)
				{
					if (sudokuBoard[i][k] != EMPTY_CELL)
					{
						if ((k == k - (k % 3)) && k != 0)
							printf(" |");
						printf("  %d ", sudokuBoard[i][k]);
					}
					else
					{
						if ((k == k - (k % 3)) && k != 0)
							printf(" |");
						printf("  %c ", SPACE);
					}
				}
				printf("\n");

			}
		}
	}

	printf(" ");
	for (k = 0; k < 6; k++)
	{
		printf("-------");
	}
	printf("--\n\n");
}


int FillBoard(short board[][9], Array*** possibilities)
{
	int boardStatus , xCoord, yCoord, gameStatus;
	
	boardStatus = OneStage(board, possibilities, &xCoord, &yCoord);

	while(boardStatus == NOT_FINISH)
	{
		if (!fillUserChoice(board, possibilities, xCoord, yCoord))
			boardStatus = FINISH_FAILURE;

		else
			boardStatus = OneStage(board, possibilities, &xCoord, &yCoord);

	}

	if (boardStatus == FINISH_SUCCESS)
	{
		printf("Success\n");
		gameStatus = FILLED;
	}

	else if (boardStatus == FINISH_FAILURE)
	{
		printf("Game over\n");
		gameStatus = FAIL;
	}

	return gameStatus;
}


bool fillUserChoice(short board[][9], Array*** possibilities, int xCoord, int yCoord)
{
	int i, j, arrSize; 
	int digitChosen;
	arrSize = (possibilities[xCoord][yCoord])->size;
	printf("\n Cell [%d,%d] holds the minimum number of possible digits, please select one of the options below", xCoord, yCoord);

	for (i = 0, j=1 ; i < arrSize; i++, j++)
	{
		printf("\n%d.%d\n", j, possibilities[xCoord][yCoord]->arr[i]);
	}

	scanf("%d", &digitChosen);

	digitChosen--;

	/* isValidNum checks if the number is a legal option at a given location - returns true if legal*/
	if (isValidNum(possibilities[xCoord][yCoord]->arr[digitChosen], board, xCoord, yCoord))
	{
		/*setting the value in the game board */
		board[xCoord][yCoord] = (possibilities[xCoord][yCoord]->arr)[digitChosen];

		/* freeing the cell in possibilities board */
		possibilities[xCoord][yCoord]->arr = (short*)realloc(possibilities[xCoord][yCoord]->arr,  (--arrSize)*sizeof(short));

		checkAlloc(possibilities[xCoord][yCoord]->arr);
		return true;
	}
	else
		return false;

}