#include "ActivePlayersFunctions.h"

PlayersList* CreateActivePlayersList()
{
	int X; // active players list length
	PlayerListNode* curr = NULL;
	PlayerListNode* prev = NULL;

	printf("\n");
	printf("Please enter the number of active players: ");
	scanf("%d", &X);
	PlayersList* activePlayers = (PlayersList*)malloc(sizeof(PlayersList));
	makeEmptyPlayersList(activePlayers);
	activePlayers->listLen = X;
	char name[MAX_LEN];

	for (; X > 0; X--)
	{

		printf("\n");
		printf("Please enter player's name: ");
		scanf("%s", name);
		curr = playersListNodeCreation(createPlayer(name)); // creating a player with the given name and creates a PlayerListNode with the same player
		if (prev == NULL) // if that's the first node created, then it's the head of the list
			activePlayers->head = curr;
		activePlayers->tail = curr;  // the last node created will be the tail of the list
		curr->prev = prev;
		prev = curr;
	}
	return activePlayers;
}
Player* createPlayer(char name[MAX_LEN])
{
	Player* player = (Player*)malloc(sizeof(Player));//memAlloc
	checkAlloc(player);
	player->board = randBoardCreation(boardListCreation()); // creates a random game board for the player
	player->name = *name; // received name is inserted to the struct
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
bool isEmptyPlayersList(PlayersList* lst)
{
	return (lst->head == NULL);
}//checks if the playerlist is empty
void makeEmptyPlayersList(PlayersList* lst)
{
	lst->head = lst->tail = NULL;
}//resets a player list after creation
PlayerListNode* playersListNodeCreation(Player* player)
{
	PlayerListNode* node = (PlayerListNode*)malloc(sizeof(PlayerListNode));
	checkAlloc(node);
	node->player = player;
	return node;
}// creates a player node for players list

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