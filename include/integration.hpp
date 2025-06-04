#ifndef INTEGRATION_HPP
#define INTEGRATION_HPP

#include "load_data.hpp"

void print_input(FunctionData data);
double calculate_f(std::vector<double> ai, double x);
double rectangual(int n, std::vector <double> x, std::vector <double> ai);
double trapezoid(int n, std::vector <double> x, std::vector <double> ai);
double simpson(int n, std::vector <double> x, std::vector <double> ai);
double simpson(int n, std::vector <double> x, double (*f)(double));
double subdivided_quadrature(int parts, int n, std::vector<double> wi, std::vector<double> xi, std::pair<double, double> ab, double (*f)(double));
double quadrature(int n, std::vector <double> x, std::vector <double> wi, std::pair <double, double> ab, double (*f)(double));

double integrate(int n, std::vector <double> ai, std::pair <double, double> ab);
double integrate(int n, double (*f)(double), std::pair <double, double> ab);

#endif 