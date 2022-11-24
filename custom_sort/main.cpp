#include<iostream>
#include<string>

#include "edge_sort.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cerr << "One argument expected for the file loction but " 
		<< argc -1 << " where given" << std::endl; 
		return -1;
	}

	Edge_Sort edge_sort = Edge_Sort();

	std::string edge_list(argv[1]);
	if (! edge_sort.read_edge_list(edge_list) ) {
		std::cerr << "Failed to read edge list" << std::endl;
		return -1;
	}

	return 0;
}

