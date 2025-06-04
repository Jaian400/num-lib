#ifndef DIFFERNTIAL_EQUATION
#define DIFFERNTIAL_EQUATION

#include <iostream>
#include <vector>

std::vector <double> solve_differential_equation(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <std::pair<double, double>> solve_differential_equation_with_x(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));

std::vector <double> solve_heuna(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <double> solve_midpoint(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <double> solve_runge_kutty(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));

#endif 