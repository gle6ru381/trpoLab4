#include "board.h"

void pair_free(Pair pair)
{
    string_free(pair.first);
    string_free(pair.second);
}

String* string_new(size_t size)
{
    String* string = (String*)(malloc(sizeof(String)));
    if (string == NULL)
        return NULL;
    string->str = (char*)(calloc(size, sizeof(char)));
    if (string->str == NULL) {
        free(string);
        return NULL;
    }
    string->capacity = size;
    string->size = 0;
    return string;
}

void string_free(String* string)
{
    free(string->str);
    free(string);
}

String* string_copy(const String* string)
{
    String* s = string_new(string->capacity);
    if (s == NULL)
        return NULL;

    memcpy(s->str, string->str, string->size * sizeof(char));

    s->size = string->size;
    return s;
}

char strAt(String* string, size_t index)
{
    if (string->size > index)
        return string->str[index];
    exit(EXIT_FAILURE);
}

int string_push_back(String* str, char c)
{
    if (str->size == str->capacity) {
        char* temp = str->str;
        str->str = realloc(str->str, (str->capacity * 2) * sizeof(char));
        if (str->str == NULL) {
            free(temp);
            return -1;
        }
        str->capacity *= 2;
    }

    str->str[str->size] = c;
    str->size++;
    return 0;
}

void swap(Figure* first, Figure* second)
{
    Figure temp = *first;
    *first = *second;
    *second = temp;
}

bool chInStr(char c, const char* string)
{
    for (int i = 0; i < strlen(string); i++) {
        if (c == string[i])
            return true;
    }
    return false;
}

Figure* boardAt(Figure board[SIZE][SIZE], char row, char col)
{
    return &board[row - '1'][col - 'a'];
}

bool move(Figure board[SIZE][SIZE], Pair pair, Side side)
{
    char typeFigure = '\0', totalFigure = '\0';
    if (isupper(strAt(pair.first, 0))) {
        if (strAt(pair.first, 0) >= 'A' && strAt(pair.first, 0) <= 'H') {
            pair.first->str[0] = tolower(pair.first->str[0]);
        } else if (chInStr(strAt(pair.first, 0), "QKPBNR")) {
            typeFigure = strAt(pair.first, 0);
        } else {
            return false;
        }
    }
    size_t i;
    if (typeFigure == '\0')
        i = 0;
    else
        i = 1;

    char bCh, bNum, eCh, eNum;
    size_t iCh, iNum;
    while (i < pair.first->size) {
        if (strAt(pair.first, i) >= 'a' && strAt(pair.first, i) <= 'h') {
            bCh = strAt(pair.first, i);
            iCh = i;
        }
        if (strAt(pair.first, i) >= '1' && strAt(pair.first, i) <= '9') {
            bNum = strAt(pair.first, i);
            iNum = i;
        }
        i++;
    }
    if (iCh > iNum)
        return false;
    if (typeFigure != '\0'
        && toupper(typeFigure) != board[bNum - '1'][bCh - 'a'].name)
        return false;

    i = 0;
    while (i < pair.second->size) {
        if (strAt(pair.second, i) >= 'a' && strAt(pair.second, i) <= 'h') {
            if (strAt(pair.second, i + 1) == '.')
                continue;
            eCh = strAt(pair.second, i);
            iCh = i;
        }
        if (strAt(pair.second, i) >= '1' && strAt(pair.first, i) <= '9') {
            eNum = strAt(pair.second, i);
            iNum = i;
        }
        if (chInStr(strAt(pair.second, i), "QKPNBR")) {
            if (i < iCh && i < iNum)
                return false;
            totalFigure = strAt(pair.second, i);
        }
        i++;
    }
    if (iCh > iNum)
        return false;
    int rangeNum = eNum - bNum;
    int rangeCh = eCh - bCh;
    Figure* mainFigure = boardAt(board, bNum, bCh);
    Figure* endFigure = boardAt(board, eNum, eCh);
    if (mainFigure->name == ' ')
        return false;
    if (mainFigure->name == 'P') {
        if (mainFigure->side == white && rangeNum < 0)
            return false;
        if (mainFigure->side == black && rangeNum > 0)
            return false;
        if (pair.separator == '-') {
            if (rangeCh != 0)
                return false;
            if (endFigure->name != ' ')
                return false;
            if (abs(rangeNum) < 3) {
                if (!mainFigure->first_move && abs(rangeNum) > 1)
                    return false;
            }
            if (totalFigure) {
                boardAt(board, bNum, bCh)->name = totalFigure;
            }

            boardAt(board, bNum, bCh)->first_move = false;
            swap(boardAt(board, bNum, bCh), boardAt(board, eNum, eCh));
        } else if (pair.separator == 'x') {
            if (abs(rangeNum) > 1)
                return false;
            if (endFigure->name == ' ')
                return false;
            if (endFigure->side == side)
                return false;
            if (rangeCh == 0 && abs(rangeCh) > 1)
                return false;
            endFigure->first_move = false;
            endFigure->name = mainFigure->name;
            endFigure->side = mainFigure->side;
            mainFigure->side = empty;
            mainFigure->name = ' ';
        }
    }
    return true;
}