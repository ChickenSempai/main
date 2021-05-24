#ifndef HUMAN_H
#define HUMAN_H

#include "_hex.h"
#include "actor.h"

class Human : public actor {
public:
    Human(tpHex color) : actor(color, Role::Human) {};
    ~Human(){}
    int move(_hex& board);
};


#endif // HUMAN_H
