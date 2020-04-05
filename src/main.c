#include "board.h"
#include "board_print_plain.h"
#include "board_read.h"

int main()
{
    Figure board[SIZE][SIZE]
            = {{{'R'}, {'N'}, {'B'}, {'Q'}, {'K'}, {'B'}, {'N'}, {'R'}},
               {},
               {},
               {},
               {},
               {},
               {},
               {{'R'}, {'N'}, {'B'}, {'Q'}, {'K'}, {'B'}, {'N'}, {'R'}}};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j].side = white;
            board[i][j].first_move = true;
        }
    }

    for (int i = SIZE - 1; i >= SIZE - 2; i--) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j].side = black;
            board[i][j].first_move = true;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        board[SIZE - 2][i].name = 'P';
    }

    for (int i = 0; i < SIZE; i++) {
        board[1][i].name = 'P';
    }

    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j].first_move = true;
            board[i][j].name = ' ';
            board[i][j].side = empty;
        }
    }

    int i = 1;
    while (true) {
        printf("%d. ", i++);
        Pair whiteMove = board_read();
        Pair blackMove = board_read();

        bool one = move(board, whiteMove, white);
        bool two = false;
        if (one)
            two = move(board, blackMove, black);
        if (!two)
            return -1;

        printf("%d\n", one);
        printf("%d\n", two);

        pair_free(whiteMove);
        pair_free(blackMove);

        board_print(board);
    }
    return 0;
}