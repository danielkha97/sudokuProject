#include "WinningPlayersFunctions.h"

void printWinners(PlayersList* winners)
{
	PlayerListNode* curr = winners->head;

	while (curr != NULL)
	{
		printf("\nPlayer's name: %s\n", curr->player->name);
		sudokoPrintBoard(curr->player->board);
		printf("\n");
		curr = curr->next;
	}
}


