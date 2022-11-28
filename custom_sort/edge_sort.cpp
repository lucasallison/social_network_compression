#include "edge_sort.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>

Edge_Sort::Edge_Sort() {}

Edge_Sort::~Edge_Sort()
{
    if (_adjacency_mat != nullptr)
    {
        for (int i = 0; i < _node_count; i++)
        {
            delete[] _adjacency_mat[i];
        }
        delete[] _adjacency_mat;
    }
}

// TODO clean up this function a bit
bool Edge_Sort::read_edge_list(const std::string &edge_list)
{
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, node;

    std::map<std::string, int> node_identifier_to_index;
    int node_ind = 0;

    std::fstream file(edge_list, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            // TODO add support for more formats
            while (std::getline(str, node, ' '))
            {
                row.push_back(node);

                if (node_identifier_to_index.count(node) == 0)
                {
                    node_identifier_to_index.insert({node, node_ind});
                    node_ind++;
                }
            }
            content.push_back(row);
        }
    }
    else
    {
        std::cerr << "Could not open the file\n";
        return false;
    }

    _node_count = node_ind;

    // Allocate the adjacency list
    _adjacency_mat = new int *[_node_count];
    for (int i = 0; i < _node_count; i++)
        _adjacency_mat[i] = new int[_node_count];

    // Set all entries to 0
    for (int i = 0; i < _node_count; i++)
    {
        for (int j = 0; j < _node_count; j++)
        {
            _adjacency_mat[i][j] = 0;
        }
    }

    int source_node_index = 0, target_node_index = 1;

    // Set existing edges to 1
    for (int i = 0; i < int(content.size()); i++)
    {
        int source, target;
        source = node_identifier_to_index[content[i][source_node_index]];
        target = node_identifier_to_index[content[i][target_node_index]];
        _adjacency_mat[source][target] = 1;

        if (_node_identifier.count(source) == 0)
            _node_identifier.insert({source, content[i][source_node_index]});

        if (_node_identifier.count(target) == 0)
            _node_identifier.insert({target, content[i][target_node_index]});
    }

    return true;
}

int Edge_Sort::compare_nodes(const int i, const int j, int *degree_i, int *degree_j)
{
    if (_adjacency_mat == nullptr)
        return -1;

    *degree_i = 0;
    *degree_j = 0;

    int overlapping_successors = 0;
    for (int e = 0; e < _node_count; e++)
    {
        *degree_i += _adjacency_mat[i][e];
        *degree_j += _adjacency_mat[j][e];

        if (_adjacency_mat[i][e] == 1 && _adjacency_mat[j][e] == 1)
            overlapping_successors++;
    }

    return overlapping_successors;
}

bool Edge_Sort::write_sorted_nodes_to_file(std::list<int> &order, const std::string &sorted_list_dest)
{
    std::ofstream file(sorted_list_dest);

    std::vector<int> order_mapping(_node_count);
    int index = 0;
    for (auto const &node : order)
    {
        order_mapping[node] = index;
        index++;
    }

    for (auto const &node : order)
    {

        std::vector<int> successors;

        for (int j = 0; j < _node_count; j++)
        {
            if (_adjacency_mat[node][j] == 1)
                successors.push_back(j);
        }

        std::sort(successors.begin(), successors.end(), [order_mapping](const int &i, const int &j)
                  { return order_mapping[i] < order_mapping[j]; });

        file << _node_identifier[node] << ": ";
        for(auto const &n : successors)
                file << _node_identifier[n] << " ";
        file << std::endl;
    }

    file.close();
    return true;
}

bool Edge_Sort::sort(const std::string &sorted_list_dest)
{
    std::cerr << "Call a child class to sort" << std::endl;
    return true;
}