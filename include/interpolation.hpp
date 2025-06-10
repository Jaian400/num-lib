#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "load_data.hpp"

double interpolate(const FunctionData& data, double userInput, int n);
// Find interpolated point
// x,f - vectors of known points (x,f) in the function 
// n - amount of points taken for interpolation
// xp - point x for interpolation
double interpolate(std::vector<double> x, std::vector<double> f, int n, double xp);

// Find interpolated point
// x,f - vectors of known points (x,f) in the function 
// xp - point x for interpolation
double interpolate(std::vector<double> x, std::vector<double> f, double xp);
void lagrange_program(int step);

#endif
