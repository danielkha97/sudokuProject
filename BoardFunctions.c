
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
	int i, xPos, yPos;

	for (i = 0; i < SIZE && flag; i++) // checks row and col of the current cell
	{
		if (sudokuBoard[row][i] == num || sudokuBoard[i][col] == num)
			flag = false;

	}

	if (flag) // if true, checks the entire cube of the current cell
	{
		xPos = row - (row % 3); // Retrieves y  for the current cube that we're gonna check
		yPos = col - (col % 3); // Retrieves x and y starting values for the current cube that we're gonna check

		for (i = 0; i < 3 && flag; i++)
		{
			if (sudokuBoard[xPos + i][yPos] == num || sudokuBoard[xPos + i][yPos + 1] == num || sudokuBoard[xPos + i][yPos + 2] == num)
				flag = false;
		}
	}

	return flag;
}
/* This function fills in the locations with only 1 option */
int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
	int singles = 0, emptyCells = 0, minLength = 9;
	bool flag = true;/* the flag is true as long as there are single option cells to fill - when there aren't the while loop will stop and the correct case is returned */

	while (flag == true)
	{
		if (singles == 0)
			flag = false;

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				/* step 1 - checking each cell for length of possibilities array */

				/* here we check the possibilities array isn't empty and lentgh equals to 1 (for 1 cell in the mat) */
				if ((possibilities[i][j] != NULL && possibilities[i][j]->size == 1))				
                {
					flag = true; /* since there's a single cell, the board will be updated and the loop needs to repeat once more */
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
						flag = false;
						x = NULL;
						y = NULL;
						return FINISH_FAILURE;
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
		if (flag)
			possibilities = PossibleDigits(board);/* we update the possibilities board is there were changes to the board */

		/* now checking if the board was filled entirely */
		if (emptyCells == 0)
		{
			x = NULL;
			y = NULL;
			return FINISH_SUCCESS;
		}

	}
	return NOT_FINISH;
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
