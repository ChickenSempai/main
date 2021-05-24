#ifndef HUMAN_H
#define HUMAN_H

#include "_hex.h"
#include "actor.h"

class Human : public actor {
public:
    Human(tpHex color) : actor(color, Role::Human) {};
    ~Human(){}
    int move(_hex& board)
    {
        int temp=0;
        static bool first = true;
        if (first) {

            first = false;
        }
        else;


        board.set_node(temp, color);
        return temp;
    }
};


#endif // HUMAN_H
