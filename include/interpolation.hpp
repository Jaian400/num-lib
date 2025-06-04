#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "load_data.hpp"

double interpolate(const FunctionData& data, double userInput, int n);
void lagrange_program(int step);

#endif
