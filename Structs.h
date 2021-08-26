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
	char* name;
	short **board;
	Array ***possibiltiesMatrix;

}Player;

typedef struct _PlayerListNode
{
	struct _PlayerListNode* next;
	struct _PlayerListNode* prev;
	Player *player;

}PlayerListNode;

typedef struct _PlayersList {

	int listLen;
	struct _PlayerListNode* head;
	struct _PlayerListNode* tail;


}PlayersList;

typedef struct _ListNode {

	Cell *coordinates;
	struct _listnode* next;
	struct _listnode* prev;


}ListNode;
typedef struct _List {

	int listLen;
	struct _ListNode* head;
	struct _ListNode* tail;

}List;

#endif  /* Structs_h */