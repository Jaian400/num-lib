#ifndef APROXIMATION_HPP
#define APROXIMATION_HPP

#include "load_data.hpp"
#include <math.h>

static int counter = 0;
static double (*original_function)(double) = nullptr;
const int INTEGRATION_N = 50;

std::vector<double> approximate(std::vector <double>base, std::pair<double, double> ab, double (*f)(double));
double base_func(double x);
double base_times_func(double x);

#endif 