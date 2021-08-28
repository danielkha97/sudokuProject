#include "WinningPlayersFunctions.h"


void gamePlay(PlayersList* activePlayers, PlayersList* winners, PlayerTree* tree)
{
	//loop while the active players isn't empty

	//tree scanning (in order)

	//for every player -> oneStage 
	  //if onestage-> FINISH_SUCCESS
		//winner -> delete from active players list, TNODE pointing to NULL
	  //if lost -> FINISH_FAILURE
		// LOSER - > delete from active player list, TNODE pointing to NULL
	  //if the game isn't finished -> NOT_FINISH 
		// getting user's input and using FillBoard to continue

}