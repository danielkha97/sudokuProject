#include <stdio.h>
#include "Structs.h"
#include "BoardFunctions.h"

void main()

{


    short board[9][9] =
            { 5,-1, 4,-1, 7,-1,-1, 1,-1,

              6,-1, 2, 1,-1,-1, 3,-1,-1,

              1,-1, 8,-1, 4,-1,-1, 6,-1,

              -1, 5,-1,-1, 6,-1,-1, 2,-1,

              -1, 2,-1, 8,-1, 3,-1,-1,-1,

              -1,-1,-1,-1,-1, 4,-1, 5, 6,

              -1, 6, 1, 5, 3, 7, 2, 8, 4,

              -1, 8, 7,-1, 1, 9,-1, 3,-1,

              -1,-1,-1, 2, 8,-1,-1,-1, 9 };

    Array*** possible_solutions;
    printf("Initial board\n");
    sudokoPrintBoard(board);
    printf("Press enter to start playing...\n");
    getchar();



    possible_solutions = PossibleDigits(board);

    
    if (FillBoard(board, possible_solutions) == -1)
        printf("User's selections led to duplications\n");

    else
    {
        sudokoPrintBoard(board);
        printf("Board filled successfully\n");
    }
     



    // Don't forget to free memory!

}