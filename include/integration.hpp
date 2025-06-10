#ifndef INTEGRATION_HPP
#define INTEGRATION_HPP

#include "load_data.hpp"

void print_input(FunctionData data);
// Calculate value of polynomial
// ai - terms of the polynomial
// x - argument 
double calculate_f(std::vector<double> ai, double x);
// Integrate polynomial using rectangle method
// ai - terms of the polynomial
// x - points of integration
// n - number of integration intervals
double rectangual(std::vector <double> ai, std::vector <double> x, int n=1000);
// Calculate value of polynomial using trapezoid method
// ai - terms of the polynomial
// x - points of integration
// n - number of integration intervals
double trapezoid(std::vector <double> ai, std::vector <double> x, int n=500);
// Calculate value of polynomial using simpson method
// ai - terms of the polynomial
// x - points of integration
// n - number of integration intervals
double simpson(std::vector <double> ai, std::vector <double> x, int n=100);
// Calculate value of polynomial using simpson method
// f - integrated function
// x - points of integration
// n - number of integration intervals
double simpson(double (*f)(double), std::vector <double> x, int n=100);
// Subdvied quadrature - splited into intervals for precision
// parts - 
// n - 
// wi - 
// 
double subdivided_quadrature(int parts, int n, std::vector<double> wi, std::vector<double> xi, std::pair<double, double> ab, double (*f)(double));
// 
double quadrature(int n, std::vector <double> x, std::vector <double> wi, std::pair <double, double> ab, double (*f)(double));

// Definite integration
// ai - terms of the polynomial
// [a, b] - interval of integration
// n - number of 
double integrate(std::vector <double> ai, std::pair <double, double> ab, int n=100);
double integrate(double (*f)(double), std::pair <double, double> ab, int n=100);

#endif 