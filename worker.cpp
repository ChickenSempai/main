#include "worker.h"


void Worker::process()
{
    if (_agent2 != nullptr){
        if (qul){
            res=_agent1->move(*_brd);
        }
        else {
            res=_agent2->move(*_brd);
        }
        qul=!qul;
    }
    else
        res=_agent1->move(*_brd);

    emit(finished());
}
