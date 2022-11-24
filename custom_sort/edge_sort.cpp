#include "edge_sort.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

            // TODO add support for more
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

    std::map<int, std::string>::iterator it;


    // TODO DELETE
    for (it = _node_identifier.begin(); it != _node_identifier.end(); it++)
        std::cout << it->first << ' ' << it->second << std::endl;

    for (int i = 0; i < _node_count; i++)
    {
        for (int j = 0; j < _node_count; j++)
        {
            std::cout << _adjacency_mat[i][j] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < int(content.size()); i++)
    {
        for (int j = 0; j < int(content[i].size()); j++)
        {
            std::cout << content[i][j] << " ";
        }
        std::cout << "\n";
    }

    return true;
}
