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
    /*
    if (_col_ind != nullptr)
        delete[] _col_ind;

    if (_row_ptr_begin != nullptr)
        delete[] _row_ptr_begin;

    if (_row_ptr_end != nullptr)
        delete[] _row_ptr_end;
*/
}

// TODO clean up this function a bit
bool Edge_Sort::read_edge_list(const std::string &edge_list)
{
    std::cout << "Read in " << edge_list << std::endl;
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, node;
    const int src_ind = 0;
    const int tar_ind = 1;

    std::map<std::string, int> node_identifier_to_index;
    int node_ind = 0;

    std::fstream file(edge_list, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            // TODO add support for more formats, maybe as cmd line arg?
            while (std::getline(str, node, ' '))
                row.push_back(node);

            // Only add valid lines of the file
            if (row.size() == 2)
            {
                content.push_back(row);

                for (const auto &n : row)
                    if (node_identifier_to_index.count(n) == 0)
                    {
                        node_identifier_to_index.insert({n, node_ind});
                        node_ind++;
                    }
            }
        }
    }
    else
    {
        std::cerr << "Could not open the file\n";
        return false;
    }

    _node_count = node_ind;

    /* SORT NODE: PUT IN FUNCTION */
    struct
    {
        std::map<std::string, int> *mptr;
        bool operator()(const std::vector<std::string> &i, const std::vector<std::string> &j)
        {
            int i_src = (*mptr)[i[src_ind]];
            int i_tar = (*mptr)[i[tar_ind]];
            int j_src = (*mptr)[j[src_ind]];
            int j_tar = (*mptr)[j[tar_ind]];

            if (i_src == j_src)
                return i_tar < j_tar;

            return i_src < j_src;
        }
    } edge_comp;

    edge_comp.mptr = &node_identifier_to_index;

    std::sort(content.begin(), content.end(), edge_comp);

    std::cout << "File parsed: saving to memory" << std::endl;

    // Allocate arrys
    _col_ind = new int[content.size()];
    _row_ptr_begin = new int[_node_count];
    _row_ptr_end = new int[_node_count];

    int index = 0;
    for (int n = 0; n < _node_count; n++)
    {
        _row_ptr_begin[n] = index;

        while (index < int(content.size()) && node_identifier_to_index[content[index][src_ind]] == n)
        {

            int source = n;
            int target = node_identifier_to_index[content[index][tar_ind]];

            _col_ind[index] = target;

            if (_node_identifier.count(source) == 0)
                _node_identifier.insert({source, content[index][src_ind]});

            if (_node_identifier.count(target) == 0)
                _node_identifier.insert({target, content[index][tar_ind]});

            index++;
        }
        _row_ptr_end[n] = index;
    }

    std::cout << "Edge list has successfully been read" << std::endl;
    return true;
}

int Edge_Sort::compare_nodes(const int i, const int j, int *degree_i, int *degree_j)
{
    // TODO check i and j ?

    *degree_i = _row_ptr_end[i] - _row_ptr_begin[i];
    *degree_j = _row_ptr_end[j] - _row_ptr_begin[j];

    int overlapping_successors = 0;
    int j_ind = _row_ptr_begin[j];
    int i_ind = _row_ptr_begin[i];

    while (true)
    {
        if (j_ind >= _row_ptr_end[j] || i_ind >= _row_ptr_end[i])
            break;

        if (_col_ind[i_ind] == _col_ind[j_ind])
        {
            overlapping_successors++;
            i_ind++;
        }
        else if (_col_ind[i_ind] < _col_ind[j_ind])
            i_ind++;
        else
            j_ind++;
    }

    return overlapping_successors;
}

bool Edge_Sort::write_sorted_nodes_to_file(std::list<int> &order, const std::string &sorted_list_dest)
{
    std::cout << "Writing result to " << sorted_list_dest << std::endl;
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

        for (int i = _row_ptr_begin[node]; i < _row_ptr_end[node]; i++)
            successors.push_back(_col_ind[i]);

        std::sort(successors.begin(), successors.end(), [order_mapping](const int &i, const int &j)
                  { return order_mapping[i] < order_mapping[j]; });

        file << _node_identifier[node] << ": ";
        for (auto const &n : successors)
            file << _node_identifier[n] << " ";
        file << std::endl;
    }

    file.close();
    std::cout << "Succesfully wrote result to file" << std::endl;
    return true;
}

bool Edge_Sort::sort(const std::string &sorted_list_dest)
{
    std::cerr << "Call a child class to sort" << std::endl;
    return true;
}