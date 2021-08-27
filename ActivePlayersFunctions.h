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





#endif /* ACTIVE_PLAYERS_h */

