#ifndef AI_MONTECARLO_H
#define AI_MONTECARLO_H

#include <qrandom.h>
#include "_hex.h"
#include "actor.h"

class AI_MonteCarlo : public actor {
public:
    AI_MonteCarlo(tpHex color) : actor(color, Role::Monte), testing_cases(1500) {}
    ~AI_MonteCarlo(){}
    int move(_hex& board);


private:
    int testing_cases; //initializes at given number
    bool first = true;

private:

    template <class RandomAccessIterator, class URNG>
    void shuffl(RandomAccessIterator first, RandomAccessIterator last, URNG&& g);

};

#endif // AI_MONTECARLO_H
