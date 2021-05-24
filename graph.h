#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>

template <typename T>
class graph  {
public:
    graph (int nodes, T val) :node_val(nodes, val) {}
    graph(const graph& g) :node_val(g.node_val) {}
    virtual ~graph() {}
    int all_nodes() const { return node_val.size(); }
    T get_node(int x) const { return node_val[x]; }
    void set_node(int x, T val) { node_val[x] = val; }
    T operator[](int x) const { return node_val[x]; }
    std::vector<T>* get_pt() { return &node_val; }
    virtual void set_edge(int x, int a) = 0;
    virtual int get_edges(int x) = 0;
private:
    std::vector <int> edges;
protected:
    std::vector <T> node_val;
};

#endif // GRAPH_H
