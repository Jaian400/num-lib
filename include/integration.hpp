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
// Integrate polynomial using trapezoid method
// ai - terms of the polynomial
// x - points of integration
// n - number of integration intervals
double trapezoid(std::vector <double> ai, std::vector <double> x, int n=500);
// Integrate polynomial using simpson method
// ai - terms of the polynomial
// x - points of integration
// n - number of integration intervals
double simpson(std::vector <double> ai, std::vector <double> x, int n=100);
// Integrate function using simpson method
// f - integrated function
// x - points of integration
// n - number of integration intervals
double simpson(double (*f)(double), std::vector <double> x, int n=100);

// Subdvied quadrature - splited into intervals for precision
// n - number of integration intervals
// wi - integration wages
// xi - integration points 
// [a, b] - interval of integration
// f - integrated function
double subdivided_quadrature(int n, std::vector<double> wi, std::vector<double> xi, std::pair<double, double> ab, double (*f)(double));
// Integrate function using quadrature method
// f - integrated function
// xi - integration points 
// wi - integration wages
// [a, b] - interval of integration
double quadrature(double (*f)(double), std::vector <double> xi, std::vector <double> wi, std::pair <double, double> ab);

// Definite integration
// ai - terms of the polynomial
// [a, b] - interval of integration
// n - number of integration intervals
double integrate(std::vector <double> ai, std::pair <double, double> ab, int n=100);
// Definite integration
// f - integrated function
// [a, b] - interval of integration
// n - number of integration intervals
double integrate(double (*f)(double), std::pair <double, double> ab, int n=100);

#endif 