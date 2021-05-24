#ifndef ACTOR_H
#define ACTOR_H

#include "_hex.h"

enum class Role {Human, Monte, Random};

class actor {
public:
    actor(tpHex n, Role _role) : color(n), role(_role) {};
    virtual ~actor(){}
    void set_color(tpHex n) { color = n; }
    tpHex get_color() const{ return color; }
    Role get_role() const{return role;}
    virtual int move(_hex& board) = 0;
protected:
    tpHex color;
private:
    Role role;
};
#endif // ACTOR_H
