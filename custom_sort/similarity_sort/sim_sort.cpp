#include "sim_sort.h"

#include <iostream>
#include <list>

Sim_Sort::Sim_Sort() {}

bool Sim_Sort::sort(const std::string &sorted_list_dest)
{

    std::cerr << "Performing similarity sort" << std::endl;
    std::list<int> order = {};

    for (int node = 0; node < _node_count; node++)
    {
        std::list<int>::iterator insert_pos = order.begin();
        int max_num_comm_successors = 1;

        std::list<int>::iterator it = order.begin();
        for (; it != order.end(); it++)
        {
            int degree_node = 0, degree_sorted_node = 0;
            int num_comm_successors = compare_nodes(node, *it, &degree_node, &degree_sorted_node);

            if (num_comm_successors >= max_num_comm_successors)
            {
                insert_pos = it;
                if (degree_node <= degree_sorted_node) 
                    insert_pos++;

                max_num_comm_successors = num_comm_successors;
            }
        }
        order.insert(insert_pos, node);

        if (node % 1000 == 0)
        {
            std::cout << "Processed " << node << " of " << _node_count << " nodes" << std::endl;
        }
    }

    return write_sorted_nodes_to_file(order, sorted_list_dest);
}