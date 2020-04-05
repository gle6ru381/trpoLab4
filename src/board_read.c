#include "board_read.h"

Pair board_read()
{
    Pair pair;
    String* first = string_new(5);
    if (!first)
        exit(EXIT_FAILURE);
    String* second = string_new(5);
    if (!second)
        exit(EXIT_FAILURE);
    String* buff = string_new(10);
    if (!buff)
        exit(EXIT_FAILURE);
    char c;
    while ((c = getchar()) != ' ' && c != '\n') {
        if ((string_push_back(buff, c)) == -1)
            exit(EXIT_FAILURE);
    }
    if ((string_push_back(buff, '\0')) == -1)
        exit(EXIT_FAILURE);
    int i = 0;
    while (strAt(buff, i) != ' ' && strAt(buff, i) != '-'
           && strAt(buff, i) != 'x') {
        if ((string_push_back(first, strAt(buff, i))) == -1)
            exit(EXIT_FAILURE);
        i++;
    }
    if ((string_push_back(first, '\0')) == -1)
        exit(EXIT_FAILURE);
    pair.separator = strAt(buff, i);
    i++;
    while (strAt(buff, i) != '\0') {
        if ((string_push_back(second, strAt(buff, i))) == -1)
            exit(EXIT_FAILURE);
        i++;
    }
    if ((string_push_back(second, '\0')) == -1)
        exit(EXIT_FAILURE);

    pair.first = first;
    pair.second = second;

    string_free(buff);
    return pair;
}