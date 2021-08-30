#ifndef Structs_h
#define Structs_h
#define SIZE 9 //check if interrupts other files
#define MAX_LEN 100

typedef struct _Array
{
	short* arr;
	unsigned short size;
}Array;

typedef struct _cell
{
	int xCoord;
	int yCoord;
}Cell;

typedef struct _Player
{
	char *name;
	short board[SIZE][SIZE];
	Array*** possibiltiesMatrix;

}Player;

typedef struct _PlayerListNode
{
	struct _PlayerListNode* next;
	struct _PlayerListNode* prev;
	Player* player;

}PlayerListNode;

typedef struct _PlayersList {

	int listLen;
	PlayerListNode* head;
	PlayerListNode* tail;

}PlayersList;

typedef struct _ListNode {

	Cell* coordinates;
	struct _ListNode* next;
	struct _ListNode* prev;


}ListNode;

typedef struct _List {

	int listLen;
	ListNode* head;
	ListNode* tail;

}List;

typedef struct _PlayerTNODE
{
	PlayerListNode* playerLNode;
	struct _PlayerTNODE* left;
	struct _PlayerTNODE* right;
}PlayerTNODE;

typedef struct _PlayerTree
{
	PlayerTNODE* root;
}PlayerTree;

#endif  /* Structs_h */