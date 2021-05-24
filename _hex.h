#ifndef _HEX_H
#define _HEX_H

#include "graph.h"

enum class tpHex : short { Vert, Horiz, Empty = SHRT_MAX };
enum {Up_Left, Up_Right, Right, Lower_Right, Lower_Left, Left};


class _hex : public graph <tpHex> {
public:
    _hex(int sideLen) :graph(sideLen* sideLen, tpHex::Empty),
                                edges(sideLen* sideLen, std::vector <int>(6, -1)), dimens(sideLen) {}
    _hex(const _hex& h) :graph(h), edges(h.edges), dimens(h.side()) {}

    ~_hex(){}
    int side() const { return dimens; }
    void link_closest(const int& index);
    bool is_right(int pos)const { return pos % dimens == dimens - 1; }
    bool is_lower(int pos)const { return pos >= dimens * (dimens - 1); }
    bool is_left(int pos)const { return pos % dimens == 0; }
    bool is_upper(int pos)const { return pos < dimens; }

private:
    int get_edges(int){return 0;};
    int dimens;
    std::vector <std::vector<int>> edges;

protected:
    void set_edge(int x, int a) {};
};

#endif // _HEX_H
