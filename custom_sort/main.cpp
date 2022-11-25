#include <iostream>
#include <string>

#include "edge_sort.h"
#include "similarity_sort/sim_sort.h"

const std::string SIM_SORT_ARG = "similarity";

int main(int argc, char **argv)
{

	// TODO help menu

	if (argc != 3)
	{
		std::cerr << "Three argument expected but "
				  << argc - 1 << " where given." << std::endl;
		return -1;
	}

	const std::string sort_choice(argv[1]);
	Edge_Sort *edge_sorter = nullptr;

	if (sort_choice.compare(SIM_SORT_ARG) == 0)
	{
		edge_sorter = new Sim_Sort();
	}
	else
	{
		std::cerr << sort_choice << " sorting has not been implemented." << std::endl;
		// TODO fix this with error handling
		return -1;
	}

	std::string edge_list(argv[2]);
	if (!edge_sorter->read_edge_list(edge_list))
	{
		std::cerr << "Failed to read edge list" << std::endl;
		return -1;
	}

	edge_sorter->sort();

	delete edge_sorter;

	return 0;
}
