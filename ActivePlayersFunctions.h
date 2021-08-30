#ifndef ACTIVE_PLAYERS_h
#define ACTIVE_PLAYERS_h

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "GeneralFunctions.h"
#include "BoardFunctions.h"



//Players list functions
bool isEmptyPlayersList(PlayersList* lst);
void makeEmptyPlayersList(PlayersList* lst);
void addPlayerNodeToList(PlayerListNode* player, PlayersList* list);

//creates a player list node from a given player
PlayerListNode* playersListNodeCreation(Player* player);
//Players list functions
bool isEmptyPlayersList(PlayersList* lst);
void makeEmptyPlayersList(PlayersList* lst);
PlayersList* CreateActivePlayersList(int* numOfPlayers); // receives the number of active players list and creates the list from user's input
PlayerListNode* playersListNodeCreation(Player* player ,PlayerListNode* prev, PlayerListNode* next); //creates a player list node from a given player
void insertPlayerDataToEndDList(PlayersList* dlst, Player* currPlayer);
void insertPlayerNodeToEndDList(PlayersList* dlst, PlayerListNode* newTail);

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

/* there are the function for the actual game play for the active players */
void startGame();
void gamePlay(PlayersList* activePlayers, PlayersList* winners, PlayerTree* tree);
void printSudokuLogo();
void playersTurn(PlayerTNODE* node, PlayersList* activePlayers, PlayersList* winners);
void treeScan(PlayerTNODE* node, PlayersList* activePlayers, PlayersList* winners, int* x, int* y);

#endif /* ACTIVE_PLAYERS_h */

