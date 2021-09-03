#ifndef  WINNING_PLAYERS_h
#define WINNING_PLAYERS_h

#include "GeneralFunctions.h"

/*prints the winners list and boards*/
void printWinners(PlayersList* winners);
/*after winners printed this func releases the list*/
void freeWinnersList(PlayersList* list);

#endif /* WINNING_PLAYERS_h */
