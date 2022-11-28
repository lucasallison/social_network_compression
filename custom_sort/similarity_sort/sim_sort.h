#ifndef __SIM_SORT_H__
#define __SIM_SORT_H__

#include "../edge_sort.h"

class Sim_Sort : public Edge_Sort
{

public:
    Sim_Sort();
    bool sort(const std::string &sorted_list_dest);
};

#endif /* __SIM_SORT_H__ */