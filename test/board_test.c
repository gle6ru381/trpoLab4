#include "board.h"
#include "board_print_plain.h"
#include "board_read.h"
#include "ctest.h"

Pair make_pair(char *one, char *two, char separator) {
  String *stringOne = string_new(strlen(one) + 1);
  for (int i = 0; i <= strlen(one); i++) {
    string_push_back(stringOne, one[i]);
  }
  String *stringTwo = string_new(strlen(two) + 1);
  for (int i = 0; i <= strlen(two); i++) {
    string_push_back(stringTwo, two[i]);
  }

  Pair pair = {stringOne, stringTwo, separator};
  return pair;
}

CTEST(board_test, test_move) {
  Figure board[SIZE][SIZE] = {
      {{'R'}, {'N'}, {'B'}, {'Q'}, {'K'}, {'B'}, {'N'}, {'R'}},
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

  FILE *fin = fopen("test.txt", "r");

  while (!feof(fin)) {
    Pair whiteMove = board_read(fin);
    Pair blackMove = board_read(fin);

    ASSERT_EQUAL(true, move(board, whiteMove, white));
    ASSERT_EQUAL(true, move(board, blackMove, black));
  }
}