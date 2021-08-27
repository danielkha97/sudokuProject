#ifndef ACTIVE_PLAYERS_h
#define ACTIVE_PLAYERS_h

#include "Structs.h"
#include "BoardFunctions.h"


//Players list functions
bool isEmptyPlayersList(PlayersList* lst);
void makeEmptyPlayersList(PlayersList* lst);
PlayersList* CreateActivePlayersList();// receives the number of active players list and creates the list from user's input
PlayerListNode* playersListNodeCreation(Player* player);//creates a player list node from a given player

//Creates a new var from type Player
Player* createPlayer(char name[MAX_LEN]);



//Player tree functions

PlayerTNODE* createNewTNODE(PlayerListNode* data, PlayerTNODE* left, PlayerTNODE* right);

/* these function build the player tree from the array of pointer to the player list's nodes*/
PlayerTree BuildPlayerTree(PlayerListNode** arr, int size);
PlayerTNODE* BuildPlayerTreeRec(PlayerListNode** arr, int size);

#endif /* ACTIVE_PLAYERS_h */

