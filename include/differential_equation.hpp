#ifndef DIFFERNTIAL_EQUATION
#define DIFFERNTIAL_EQUATION

#include <iostream>
#include <vector>

std::vector <double> solve_diff_eq_euler(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <std::pair<double, double>> solve_differential_equation_with_x(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));

std::vector <double> solve_diff_eq_heuna(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <double> solve_diff_eq_midpoint(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <double> solve_diff_eq_runge_kutty(int N, std::pair <double, double> ab, double y0, double (*f)(double, double));
std::vector <double> solve_diff_eq(std::pair <double, double> ab, double y0, double (*f)(double, double), int N=100);

#endif 