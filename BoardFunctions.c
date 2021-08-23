
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
	int singleCellsFound = 0, emptyCells, res = NOT_FINISH;
	bool isDuplicate = false;
	unsigned short minLength;;


	bool areSingleCells = true; /* the flag is true as long as there are single option cells to fill - when there aren't the while loop will stop and the correct case is returned */

	while (areSingleCells)
	{
		minLength = 9;
		areSingleCells = false;
		emptyCells = 0;

		for (int i = 0; i < SIZE && res != FINISH_FAILURE; i++)
		{
			for (int j = 0; j < SIZE && res != FINISH_FAILURE; j++)	/* step 1 - checking each cell for length of possibilities array */
			{

				/* here we check the possibilities array isn't empty and lentgh equals to 1 (for 1 cell in the mat) */
				if (possibilities[i][j] != NULL && possibilities[i][j]->size == 1)
				{
					int currNum;
					bool isDuplicate = false;
					currNum = possibilities[i][j]->arr[0];
					areSingleCells = true;/* since there's a single cell, the board will be updated and the loop needs to repeat once more */
					//singleCellsFound++;
					emptyCells++;

					if (!checkAndFill(board, possibilities, i, j, 0)) /* if this board is illegal */
					{

						areSingleCells = false;
						res = FINISH_FAILURE;
						break;
					}

					else
					{
						updatePossibilitiesMatrix(board, possibilities, i, j, currNum, &isDuplicate); /* we update the possibilities board is there were changes to the board */
						if (isDuplicate)
						{
							areSingleCells = false;
							res = FINISH_FAILURE;
							break;
						}

						else
						{
							areSingleCells = true;
							emptyCells--;
						}
					}
				}

				/* if the cell is empty & more than one possibility, checking if it's the shortest possibilities array */
				else if (possibilities[i][j] != NULL && possibilities[i][j]->size > 1)
				{
					emptyCells++;

					/* checking if this cell has the shortest array of posibilities to fill */
					if (possibilities[i][j]->size < minLength)   /* there is a problem here that needs to be fixed */
					{
						*x = i;
						*y = j;

						/* replacing the shortest length */
						minLength = possibilities[i][j]->size;
					}

				}
			}


		}
	}

	/* now checking if the board was filled entirely */
	if (emptyCells == 0)
	{
		res = FINISH_SUCCESS;
		areSingleCells = false;
	}

	else if (res != FINISH_FAILURE)
	{
		res = NOT_FINISH;
		areSingleCells = false;
	}


	return res;

}
bool checkAndFill(short board[][9], Array*** possibilities, int row, int col, int arrInd)
{

	/* isValidNum checks if the number is a legal option at a given location - returns true if legal*/
	if (isValidNum(possibilities[row][col]->arr[arrInd], board, row, col))
	{
		/*setting the value in the game board */
		board[row][col] = possibilities[row][col]->arr[arrInd];

		/* freeing the cell in possibilities board because there was only one option */
		free(possibilities[row][col]->arr);
		free(possibilities[row][col]);
		possibilities[row][col] = NULL;


		return true;
	}
	else
		return false;
}

void sudokoPrintBoard(short sudokuBoard[][9])
{
	int i, j, k;
	printf("\n\n");
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

	/*
	* 	int i, j, k;
	printf("\n\n  ");
	for (i = -1; i < SIZE; i++)
	{

		if (i == -1)
		{

			for (j = 0; j < SIZE; j++)
			{
				if (j == j - (j % 3))
					printf("|");
				printf(" %d", j);
			}
			printf("\n");
		}

		else
		{
			if (i % 3 == 0)
			{

				for (k = 0; k < 3; k++)
				{
					printf("-------");
				}

				printf("--\n ");

				printf("%d|", i);

				for (k = 0; k < SIZE; k++)
				{
					if (sudokuBoard[i][k] != EMPTY_CELL)
					{
						if ((k == k - (k % 3)) && k != 0)
							printf("|");
						printf(" %d", sudokuBoard[i][k]);
					}

					else
					{
						if ((k == k - (k % 3)) && k != 0)
							printf("|");
						printf(" %c", SPACE);
					}
				}

				printf("\n ");

			}

			else
			{

				printf("%d|", i);

				for (k = 0; k < SIZE; k++)
				{
					if (sudokuBoard[i][k] != EMPTY_CELL)
					{
						if ((k == k - (k % 3)) && k != 0)
							printf("|");
						printf(" %d", sudokuBoard[i][k]);
					}
					else
					{
						if ((k == k - (k % 3)) && k != 0)
							printf("|");
						printf(" %c", SPACE);
					}
				}

				if (i % SIZE == 2 || i % SIZE == 5 || i % SIZE == 8)
				{
					printf("\n");
				}

				else
				{
					printf("\n ");
				}


			}
		}
	}


	for (k = 0; k < 3; k++)
	{
		printf("-------");
	}
	printf("--\n");
	*/

}


int FillBoard(short board[][9], Array*** possibilities)
{
	int boardStatus, xCoord, yCoord, gameStatus;

	boardStatus = OneStage(board, possibilities, &xCoord, &yCoord);
	sudokoPrintBoard(board);

	while (boardStatus == NOT_FINISH)
	{

		if (!fillUserChoice(board, possibilities, xCoord, yCoord))  /* when the function returns false it means that the user's choice led to duplications */
			boardStatus = FINISH_FAILURE;
		else
		{
			boardStatus = OneStage(board, possibilities, &xCoord, &yCoord);
			if (boardStatus == NOT_FINISH)
				sudokoPrintBoard(board);
		}

	}

	if (boardStatus == FINISH_SUCCESS)
	{
		gameStatus = FILLED;
	}

	else if (boardStatus == FINISH_FAILURE)
	{
		gameStatus = FAIL;
	}

	freePossibilitiesBoard(possibilities);

	return gameStatus;
}


bool fillUserChoice(short board[][9], Array*** possibilities, int xCoord, int yCoord)
{
	int i, j, arrSize;
	int userChoice, chosenIndex;
	bool isDuplicate = false, res = true;
	arrSize = possibilities[xCoord][yCoord]->size;



	printf("\n Cell [%d,%d] currently holds the minimum number of possible digits, please select one of the options below:\n", xCoord, yCoord);

	for (i = 0, j = 1; i < arrSize; i++, j++)
	{
		printf(" %d. %d\n", j, possibilities[xCoord][yCoord]->arr[i]);
	}

	printf(" ");
	scanf("%d", &userChoice);

	printf(" Updating cell %d with value %d\n\n", (9 * xCoord) + yCoord, userChoice);

	chosenIndex = findIndInArray(possibilities[xCoord][yCoord]->arr, arrSize, userChoice); /* finding the ind of the digit select by the user in the array of the cell */


	if (checkAndFill(board, possibilities, xCoord, yCoord, chosenIndex))
	{
		updatePossibilitiesMatrix(board, possibilities, xCoord, yCoord, userChoice, &isDuplicate);
		if (isDuplicate)
			res = false;

		else
			res = true;

	}

	else
		res = false;

	return res;



}

int findIndInArray(short* arr, unsigned short size, int item)
{
	int left, right, mid, ind;
	ind = NOT_FOUND;
	left = 0;
	right = size - 1;

	while ((left <= right) && ind == NOT_FOUND)
	{
		mid = (left + right) / 2;
		if (arr[mid] == item)
			ind = mid;

		else if (arr[mid] < item)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return ind;
}



void updatePossibilitiesMatrix(short board[][9], Array*** possibilities, int row, int col, int num, bool* isDuplicate)
{
	/* this function go over the row and col and 3X3 matrix of a specific cell (one option digit cell) and removes and filled digit from the other empty cells*/
	short i, ind, xCoord, yCoord, prevSize, newSize;
	short j, l;
	short k = 0;


	for (i = 0; i < SIZE && *isDuplicate == false; i++) // split to functions for row, col and 3X3 matrix of the current cell
	{
		if (possibilities[row][i] != NULL)
		{
			if (i != col)
			{
				///*ind = findIndInArray(possibilities[row][i]->arr, possibilities[row][i]->size, num);
				//if (ind != NOT_FOUND)
				//{

				//	prevSize = possibilities[row][i]->size;
				//	possibilities[row][i]->size -= 1;
				//	newSize = possibilities[row][i]->size;
				//	if (newSize == 0)
				//	{
				//		*isDuplicate = true;
				//	}

				//	else
				//	{
				//		short* newArr;
				//		newArr = (short*)malloc(possibilities[row][i]->size * sizeof(short));
				//		checkAlloc(newArr);
				//		for (l = 0; l < prevSize; l++)
				//		{
				//			if (l != ind)
				//			{
				//				newArr[k] = possibilities[row][i]->arr[l];
				//				k++;
				//			}
				//		}

				//		free(possibilities[row][i]->arr);
				//		possibilities[row][i]->arr = newArr;
				//		k = 0;
				//	}*/
				//}

				duplicatecheck(possibilities, row, i, num, isDuplicate);

			}
		}

		if (possibilities[i][col] != NULL)
		{
			if (i != row)
			{
				//ind = findIndInArray(possibilities[i][col]->arr, possibilities[i][col]->size, num);
				//if (ind != NOT_FOUND)
				//{
				//	prevSize = possibilities[i][col]->size;
				//	possibilities[i][col]->size -= 1;
				//	newSize = possibilities[i][col]->size;

				//	if (newSize == 0)
				//	{
				//		*isDuplicate = true;
				//	}

				//	else
				//	{
				//		short* newArr;
				//		newArr = (short*)malloc(possibilities[i][col]->size * sizeof(short));
				//		checkAlloc(newArr);
				//		for (l = 0; l < prevSize; l++)
				//		{
				//			if (l != ind)
				//			{
				//				newArr[k] = possibilities[i][col]->arr[l]; // make a function that copies one array to another
				//				k++;
				//			}
				//		}
				//		free(possibilities[i][col]->arr);
				//		possibilities[i][col]->arr = newArr;
				//		k = 0;
				//	}


				//}


				duplicatecheck(possibilities, i, col, num, isDuplicate);
			}

		}

	}

	xCoord = row - (row % 3); // Retrieves y  for the current cube that we're gonna check
	yCoord = col - (col % 3); // Retrieves x and y starting values for the current cube that we're gonna check

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (possibilities[xCoord + i][yCoord + j] != NULL)
			{

				if (xCoord + i != row || yCoord + j != col)
				{
					/*ind = findIndInArray(possibilities[xCoord + i][yCoord + j]->arr, possibilities[xCoord + i][yCoord + j]->size, num);
					if (ind != NOT_FOUND)
					{
						prevSize = possibilities[xCoord + i][yCoord + j]->size;
						possibilities[xCoord + i][yCoord + j]->size -= 1;
						newSize = possibilities[xCoord + i][yCoord + j]->size;
						if (newSize == 0)
						{
							*isDuplicate = true;
						}

						else
						{
							short* newArr;
							newArr = (short*)malloc(possibilities[xCoord + i][yCoord + j]->size * sizeof(short));
							checkAlloc(newArr);
							for (l = 0; l < prevSize; l++)
							{
								if (l != ind)
								{
									newArr[k] = possibilities[xCoord + i][yCoord + j]->arr[l];
									k++;
								}
							}

							free(possibilities[xCoord + i][yCoord + j]->arr);
							possibilities[xCoord + i][yCoord + j]->arr = newArr;
							k = 0;
						}
					}*/

					duplicatecheck(possibilities, xCoord + i, yCoord + j, num, isDuplicate);
				}
			}
		}
	}
}
void duplicatecheck(Array*** possibilities, int xCord, int yCord, int num, bool* isDuplicate)
{
	short ind, prevSize, newSize, l, k = 0;
	ind = findIndInArray(possibilities[xCord][yCord]->arr, possibilities[xCord][yCord]->size, num);
	if (ind != NOT_FOUND)
	{
		prevSize = possibilities[xCord][yCord]->size;
		newSize = prevSize - 1;
		possibilities[xCord][yCord]->size = newSize;
		if (newSize == 0)
		{
			*isDuplicate = true;
		}

		else
		{
			short* newArr;
			newArr = (short*)malloc(newSize * sizeof(short));
			checkAlloc(newArr);
			for (l = 0; l < prevSize; l++)
			{
				if (l != ind)
				{
					newArr[k] = possibilities[xCord][yCord]->arr[l];
					k++;
				}
			}

			free(possibilities[xCord][yCord]->arr);
			possibilities[xCord][yCord]->arr = newArr;
		}
	}
}

void freePossibilitiesBoard(Array*** possibilities)
{
	int i, j;

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			if (possibilities[i][j] != NULL)
			{
				free(possibilities[i][j]->arr);
				free(possibilities[i][j]);
				possibilities[i][j] = NULL;
			}
		}
}