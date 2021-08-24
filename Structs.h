#ifndef Structs_h
#define Structs_h
#define SIZE 9 //check if interrupts other files

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

typedef struct _Board
{
	short*** boardStart;
}Board;

typedef struct _Player
{
	char name[100];


}Player;

typedef struct _ListNode {

	struct _cell coordinates;
	struct _listnode* next;
	struct _listnode* prev;


}ListNode;
typedef struct _List {

	struct _ListNode* head;
	struct _ListNode* tail;

}List;

#endif  /* Structs_h */