#include "ActivePlayersFunctions.h"
#include "Structs.h"
#include "GeneralFunctions.h"
#include "BoardFunctions.h"

void createActivePlayers()
{
	int X; // active players list length

	printf("\n");
	printf("Please enter the number of active players: ");
	scanf("%d", &X);
	//List ActivePlayers = createEmptyList();
	char name[MAX_LEN];

	for (; X > 0; X--)
	{
		printf("\n");
		printf("Please enter player's name: ");
		scanf("%s", name);
		createPlayer(name);
		//create node+add player

	}
}

Player* createPlayer(char name[MAX_LEN])
{
	Player* player = (Player*)malloc(sizeof(Player));
	checkAlloc(player);
	player->board = randBoardCreation(boardListCreation());
	player->name = *name;
	player->possibiltiesMatrix = PossibleDigits(player->board);
	return player;


}