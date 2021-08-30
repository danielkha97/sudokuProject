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
void freeWinnersList(PlayersList* list)
{
	PlayerListNode* temp = list->head;
	PlayerListNode* curr;
	freePlayer(list->head->player);
	for (int i = 0; i < list->listLen; i++)
	{
		curr = temp->next;
		freePlayer(temp->player);
		free(temp);
		temp = curr;
	}
	free(list);

}


