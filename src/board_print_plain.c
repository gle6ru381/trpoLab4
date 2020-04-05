#include "board_print_plain.h"

void board_print(Figure board[SIZE][SIZE])
{
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d|", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].side == white)
                printf("%2c", tolower(board[i][j].name));
            else
                printf("%2c", toupper(board[i][j].name));
        }
        printf("\n");
    }

    printf("  ");
    char c = 'a';
    for (int i = 0; i < SIZE; i++) {
        printf("%2c", c++);
    }
    printf("\n");
}