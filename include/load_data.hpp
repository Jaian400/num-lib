#ifndef LOAD_DATA_HPP
#define LOAD_DATA_HPP

#include <vector>
#include <string>
#include <iostream>

struct FunctionData {
    int N=0;
    std::vector<double> x;
    std::vector<double> fx;
};

FunctionData load_data(const std::string& filename);
void print_table(const FunctionData& func);

#endif
