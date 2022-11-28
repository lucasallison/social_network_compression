# Custom Sorting Algorithms

This subdirectory contains algorithms which order edge lists based on custom sorting algorithm, which can in turn be used by the webgraph framework to compress them. The program expects an edge list as an input and ouputs a graph in the AsciiGraph file format, as expected by the webgraph framework. It takes an edge list as input because this is commonly used by widely available datasets.

## Edge Sort Base Class

The file "edge_sort.h" contains the base class which is called in the main function. The base class can be extended by different child class implementation in order to experiment with different algorithms to sort the edges.

## Similarity Sort

Sorts the nodes based on similarity ... reference paper


## TODO's

- Currently the edge list is saved by the program as an adjacency matrix, a sparse representation should be implemented.
- Smaller TODO's are indicated by comments n the code

