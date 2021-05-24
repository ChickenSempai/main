#include "ai_weak.h"
#include <time.h>
#include <random>


int AI_weak::move(_hex& board)
{
    srand(time(0));
    int i;
    do
        i = rand() % board.all_nodes();
    while (board[i] != tpHex::Empty);
    board.set_node(i, color);
    return i;
}
