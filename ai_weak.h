#ifndef AI_WEAK_H
#define AI_WEAK_H

#include "_hex.h"
#include "actor.h"

class AI_weak : public actor {
public:
    AI_weak(tpHex color) : actor(color,  Role::Random) {};
    ~AI_weak(){}
    int move(_hex& board);
};

#endif // AI_WEAK_H
