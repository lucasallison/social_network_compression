#include <string>
#include <map>

#ifndef __EDGE_SORT_H__
#define __EDGE_SORT_H__

class Edge_Sort
{

protected:

    // Nodes are internally represented by integers
    // With this map the actual node identifier can be retrieved
    std::map<int, std::string> _node_identifier;
    int** _adjacency_mat = nullptr;
    int _node_count;

public:

    Edge_Sort();
    ~Edge_Sort();
    bool read_edge_list(const std::string& edge_list);
    void sort();
};

#endif /* __EDGE_SORT_H__ */