#include "ActivePlayersFunctions.h"
#include "Structs.h"
#include "GeneralFunctions.h"
#include "BoardFunctions.h"

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


//Players list functions
bool isEmptyPlayersList(PlayersList* lst)
{
	return (lst->head == NULL);
}
void makeEmptyPlayersList(PlayersList* lst)
{
	lst->head = lst->tail = NULL;
}
PlayerListNode* playersListNodeCreation(Player* player)
{
	PlayerListNode* node = (PlayerListNode*)malloc(sizeof(PlayerListNode));
	checkAlloc(node);
	node->player = player;
	return node;
}

//Player Tree functions
PlayerTNODE* createNewTNODE(PlayerListNode* data, PlayerTNODE* left, PlayerTNODE* right)
{
	PlayerTNODE *node = (PlayerTNODE*)malloc(sizeof(PlayerTNODE));
	checkAlloc(node);

	node->playerLNode = data;
	node->left = left;
	node->right = right;

	return node;
}
PlayerTree BuildPlayerTree(PlayerListNode** arr, int size)
{
	PlayerTree res;

	res.root = BuildPlayerTreeRec(arr, size);

	return res;
}
PlayerTNODE* BuildPlayerTreeRec(PlayerListNode** arr, int size)
{
	PlayerTNODE* left, * right, *root;

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