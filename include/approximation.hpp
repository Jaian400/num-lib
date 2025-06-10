#ifndef APROXIMATION_HPP
#define APROXIMATION_HPP

#include "load_data.hpp"
#include <math.h>

static int counter = 0;
static double (*original_function)(double) = nullptr;
const int INTEGRATION_N = 50;

// Aproximate the function
// [a, b] - interval of x
// f - referenced function
// N - size of standard base
std::vector<double> approximate(std::pair<double, double> ab, double (*f)(double), int N=15);
double base_func(double x);
double base_times_func(double x);

#endif 