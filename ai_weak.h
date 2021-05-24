#ifndef AI_WEAK_H
#define AI_WEAK_H

#include <qrandom.h>
#include "_hex.h"
#include "actor.h"
#include <time.h>
#include <random>

class AI_weak : public actor {
public:
    AI_weak(tpHex color) : actor(color,  Role::Random) {};
    ~AI_weak(){}
    int move(_hex& board)
    {
        srand(time(0));
        int i;
        do
            i = rand() % board.all_nodes();
        while (board[i] != tpHex::Empty);
        board.set_node(i, color);
        return i;
    }
};

#endif // AI_WEAK_H
