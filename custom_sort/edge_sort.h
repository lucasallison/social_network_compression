#ifndef __EDGE_SORT_H__
#define __EDGE_SORT_H__

#include <string>
#include <map>
#include <list>

const uint MAX_NUM_NODES = 100000;

struct Sparse_Matrix
{
    int col_ind[MAX_NUM_NODES * MAX_NUM_NODES] = {0};
    int row_ptr_begin[MAX_NUM_NODES] = {0};
    int row_ptr_end[MAX_NUM_NODES] = {0};
};

class Edge_Sort
{
private:
    void free_adjacency_mat();
    void free_sparse_mat();

    // TODO make a function which reads it in directly
    void convert_adj_mat_to_s_mat();

protected:
    // Nodes are internally represented by integers
    // With this map the actual node identifier can be retrieved
    std::map<int, std::string> _node_identifier;
    int **_adjacency_mat = nullptr;
    int _node_count;

    bool _is_sparse = false;
    Sparse_Matrix *_s_mat = nullptr;

    // Return the number of successors the have in common and their respective degrees
    int compare_nodes(const int i, const int j, int *degree_i, int *degree_j);

    bool write_sorted_nodes_to_file(std::list<int> &order, const std::string &sorted_list_dest);

public:
    Edge_Sort();

    virtual ~Edge_Sort();

    bool read_edge_list(const std::string &edge_list, bool sparse_matrix);

    virtual bool sort(const std::string &sorted_list_dest);
};

#endif /* __EDGE_SORT_H__ */