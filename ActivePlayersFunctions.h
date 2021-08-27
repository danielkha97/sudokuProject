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
//Players list functions
bool isEmptyPlayersList(PlayersList* lst);
void makeEmptyPlayersList(PlayersList* lst);
PlayersList* CreateActivePlayersList();// receives the number of active players list and creates the list from user's input
PlayerListNode* playersListNodeCreation(Player* player);//creates a player list node from a given player

//Creates a new var from type Player
Player* createPlayer(char name[MAX_LEN]);

// sorting the array woth ,mergesort by the required criteria
void mergeSort(PlayerListNode** arr, int l, int r);
void merge(PlayerListNode** arr, int p, int q, int r);

//Player tree functions
PlayerTNODE* createNewTNODE(PlayerListNode* data, PlayerTNODE* left, PlayerTNODE* right);

/* these function build the player tree from the array of pointer to the player list's nodes*/
PlayerTree BuildPlayerTree(PlayerListNode** arr, int size);
PlayerTNODE* BuildPlayerTreeRec(PlayerListNode** arr, int size);

#endif /* ACTIVE_PLAYERS_h */

