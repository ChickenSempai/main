#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <actor.h>
#include "_hex.h"

class Worker :public QObject
{
    Q_OBJECT
public:
    Worker(actor *agent, _hex *board, int &res_holder):_agent1(agent), _brd(board), res(res_holder){}
    ~Worker(){}
    void addActor(actor *agent) {_agent2 = agent;}
public slots:
    void process();
signals:
    void finished();
private:
    bool qul = true;
    actor *_agent1;
    actor *_agent2 = nullptr;
    _hex *_brd;
    int &res;
};

#endif // WORKER_H
