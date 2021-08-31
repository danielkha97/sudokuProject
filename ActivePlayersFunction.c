#include "ActivePlayersFunctions.h"

// Temp
PlayersList* CreateActivePlayersList(int* numOfPlayers)
{
	int X; // activePlayers list length



	printf("\n");
	printf("    Please enter the number of active players: ");
	scanf("%d", &X);
	*numOfPlayers = X;
	PlayersList* activePlayers = (PlayersList*)malloc(sizeof(PlayersList));
	checkAlloc(activePlayers);

	makeEmptyPlayersList(activePlayers); //resets the list head and tail to NULL
	activePlayers->listLen = X;


	for (; X > 0; X--)
	{
		Player* player;
		char* name = (char*)malloc(MAX_LEN * sizeof(char));
		checkAlloc(name);
		printf("\n");
		printf("    Please enter player's name: ");
		scanf("%s", name);
		player = createPlayer(name);
		insertPlayerDataToEndDList(activePlayers, player);
	}
	return activePlayers;
}
Player* createPlayer(char* name)
{
	Player* player = (Player*)malloc(sizeof(Player));//memAlloc
	checkAlloc(player);
	randBoardCreation(boardListCreation(), player->board); // creates a random game board for the player
	player->name = name; // received name is inserted to the struct
	player->possibiltiesMatrix = PossibleDigits(player->board); // 'possibilities' board is created for the random board of the player
	return player;
}
PlayerListNode** activePlayersArrayCreation(PlayersList* activePlayers)
{
	PlayerListNode** playersArr = (PlayerListNode**)malloc(sizeof(PlayerListNode*) * activePlayers->listLen); // creating an array by the length of the players list

	if (!isEmptyPlayersList(activePlayers)) // if the players list isn't empty
	{
		PlayerListNode* curr = activePlayers->head;

		for (int i = 0; i < activePlayers->listLen; i++)// copying the pointer to each list node to the array
		{
			playersArr[i] = curr;
			curr = curr->next;

		}
	}
	mergeSort(playersArr, 0, activePlayers->listLen - 1);// using mergesort to sort the array by the required criteria
	return playersArr;
}

//Players list functions
bool isEmptyPlayersList(PlayersList* lst)//checks if the playerlist is empty
{
	return (lst->head == NULL);
}
void makeEmptyPlayersList(PlayersList* lst)//resets a player list after creation
{
	lst->head = NULL;
	lst->tail = NULL;
}
PlayerListNode* playersListNodeCreation(Player* player, PlayerListNode* prev, PlayerListNode* next)// creates a player node for players list
{
	PlayerListNode* node = (PlayerListNode*)malloc(sizeof(PlayerListNode));
	checkAlloc(node);
	node->player = player;
	node->next = next;
	node->prev = prev;
	return node;
}

//MergeSort algorithm for players Array
void mergeSort(PlayerListNode** arr, int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		// Merge the sorted subarrays
		merge(arr, l, m, r);
	}

}
void merge(PlayerListNode** arr, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	PlayerListNode** L = (PlayerListNode**)malloc(sizeof(PlayerListNode*) * n1);
	PlayerListNode** M = (PlayerListNode**)malloc(sizeof(PlayerListNode*) * n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[p + i];
	for (int j = 0; j < n2; j++)
		M[j] = arr[q + 1 + j];

	int i, j, k;
	i = 0;
	j = 0;
	k = p;

	while (i < n1 && j < n2)
	{
		//board filled cells count comparison
		if (countBoardFullCells(L[i]->player->board) < countBoardFullCells(M[j]->player->board))
		{
			arr[k] = L[i];
			i++;
		}
		else if (countBoardFullCells(L[i]->player->board) > countBoardFullCells(M[j]->player->board))
		{
			arr[k] = M[j];
			j++;
		}
		else
		{
			if (strcmp(L[i]->player->name, M[j]->player->name) <= 0) // ascending order
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = M[j];
				j++;
			}


		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = M[j];
		j++;
		k++;
	}
}

//Player Tree functions
PlayerTNODE* createNewTNODE(PlayerListNode* data, PlayerTNODE* left, PlayerTNODE* right)
{
	PlayerTNODE* node = (PlayerTNODE*)malloc(sizeof(PlayerTNODE));
	checkAlloc(node);

	node->playerLNode = data;
	node->left = left;
	node->right = right;

	return node;
}
PlayerTree BuildPlayerTree(PlayerListNode** arr, int size)
{
	int n, power;
	PlayerTree res;
	power = ceil(log(size + 1) / log(2));
	n = pow(2, power) - 1;

	arr = (PlayerListNode**)realloc(arr, n * sizeof(PlayerListNode*));
	checkAlloc(arr);

	for (int i = size; i < n; i++)
	{
		arr[i] = NULL;
	}

	res.root = BuildPlayerTreeRec(arr, n);

	return res;
}
PlayerTNODE* BuildPlayerTreeRec(PlayerListNode** arr, int size)
{
	PlayerTNODE* left, * right, * root;

	if (size == 0 || arr[size / 2] == NULL)
		return NULL;

	else
	{
		left = BuildPlayerTreeRec(arr, size / 2);
		right = BuildPlayerTreeRec(arr + (size / 2 + 1), size / 2);
		root = createNewTNODE(arr[size / 2], left, right);
	}

	return root;
}

//gamePlay functions for active players
void printSudokuLogo()
{
	printf("    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("    |   Welcome to Sudoku Game !  | \n");
	printf("    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

}

void startGame()
{

	Array*** possible_solutions;
	PlayersList* playersList, * winnersList;
	PlayerListNode** activePlayersArr;
	PlayerTree playersTree;
	int numOfPlayers = 0;

	printSudokuLogo();
	printf("    Press enter to start playing...\n");
	getchar();

	playersList = CreateActivePlayersList(&numOfPlayers);
	winnersList = (PlayersList*)malloc(sizeof(PlayersList));
	checkAlloc(winnersList);
	makeEmptyPlayersList(winnersList);
	activePlayersArr = activePlayersArrayCreation(playersList);
	playersTree = BuildPlayerTree(activePlayersArr, numOfPlayers);
	gamePlay(playersList, winnersList, &playersTree);
	if (!isEmptyPlayersList(winnersList))
		printWinners(winnersList);

	// insert a function here for freeing all of the allocated variables
}
void gamePlay(PlayersList* activePlayers, PlayersList* winners, PlayerTree* tree)
{
	while (!isEmptyPlayersList(activePlayers))
	{
		int x, y;
		treeScan(tree->root, activePlayers, winners, &x, &y);
	}

}
void addPlayerNodeToList(PlayerListNode* player, PlayersList* list)
{
	if (list->head == NULL)
	{
		list->head = player;
		list->tail = player;
		list->listLen++;
	}
	else
	{
		PlayerListNode* curr = list->head;
		for (int i = 0; i < list->listLen - 1; i++)
		{
			curr = curr->next;
		}
		curr->next = player;
		list->tail = player;
		list->listLen++;
	}
}
void removePlayerFromList(PlayerListNode* player, PlayersList* list)
{
	if (list->head == player)
	{
		if (player->next != NULL) {
			list->head = player->next;
			player->next->prev = NULL;
		}
		else
			list->head = NULL;
	}
	if (list->tail == player)
	{
		if (player->prev != NULL) {
			list->tail = player->prev;
			player->prev->next = NULL;
		}
		else
			list->tail = NULL;

	}
	if (player->prev != NULL)
	{
		if (player->next != NULL)
		{
			player->prev->next = player->next;
			player->next->prev = player->prev;
		}
		else
			player->prev->next = NULL;
	}
	if (player->next != NULL)
	{
		if (player->prev != NULL)
		{
			player->next->prev = player->prev;
			player->prev->next = player->next;
		}
		else
			player->next->prev = NULL;
	}

	list->listLen--;
	free(player);
}

void treeScan(PlayerTNODE* node, PlayersList* activePlayers, PlayersList* winners, int* x, int* y)
{
	if (node->left == NULL && node->right == NULL)
	{
		if (node->playerLNode != NULL)
			playersTurn(node, activePlayers, winners);
		return;
	}

	if (node->left != NULL && node->left->playerLNode != NULL)
		treeScan(node->left, activePlayers, winners, x, y);

	if (node->playerLNode != NULL)
		playersTurn(node, activePlayers, winners, x, y);

	if (node->right != NULL && node->right->playerLNode != NULL)
		treeScan(node->right, activePlayers, winners, x, y);

}
void playersTurn(PlayerTNODE* node, PlayersList* activePlayers, PlayersList* winners)
{
	printf("\n Current player: %s\n", node->playerLNode->player->name);


	switch (FillBoard(node->playerLNode->player->board, node->playerLNode->player->possibiltiesMatrix))
	{
	  case FINISH_SUCCESS:
	  {
		insertPlayerDataToEndDList(winners, node->playerLNode->player);
		winners->listLen++;
		sudokoPrintBoard(node->playerLNode->player->board);
		printf("\n WINNER ! \n");
		removePlayerFromList(node->playerLNode, activePlayers);
		node->playerLNode = NULL;
		break;
	  }
	  case FINISH_FAILURE:
	  {

		removePlayerFromList(node->playerLNode, activePlayers);
		node->playerLNode = NULL;
		printf("\n user's choices led to duplications  \n");
		break;

	  }

	}
}

void insertPlayerDataToEndDList(PlayersList* dlst, Player* currPlayer)
{
	PlayerListNode* newTail;

	newTail = playersListNodeCreation(currPlayer, NULL, NULL);
	insertPlayerNodeToEndDList(dlst, newTail);
}

void insertPlayerNodeToEndDList(PlayersList* dlst, PlayerListNode* newTail)
{
	if (isEmptyPlayersList(dlst))
		dlst->head = dlst->tail = newTail;
	else
	{
		newTail->prev = dlst->tail;
		newTail->next = NULL;
		dlst->tail->next = newTail;
		dlst->tail = newTail;
	}
}
//void freePlayer()
//{
//	freePossibilitiesBoard();
//	create 3 functions to free player
//}
//void freeTree

//void freeWinnersList()
//freeplayer

