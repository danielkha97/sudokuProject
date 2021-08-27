#ifndef ACTIVE_PLAYERS_h
#define ACTIVE_PLAYERS_h

#include "Structs.h"
#include "BoardFunctions.h"
#include "GeneralFunctions.h"

//Players list functions
bool isEmptyPlayersList(PlayersList* lst);
void makeEmptyPlayersList(PlayersList* lst);

// receives the number of active players list and creates the list from user's input
PlayersList* CreateActivePlayersList();

//creates a player list node from a given player
PlayerListNode* playersListNodeCreation(Player* player);

// the functions creates an array of pointers from a player list
PlayerListNode** activePlayersArrayCreation(PlayersList* activePlayers);

//Creates a new var from type Player
Player* createPlayer(char name[MAX_LEN]);

// sorting the array woth ,mergesort by the required criteria
void mergeSort(PlayerListNode** arr, int l, int r);
void merge(PlayerListNode** arr, int p, int q, int r);





#endif /* ACTIVE_PLAYERS_h */

