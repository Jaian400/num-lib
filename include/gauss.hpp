#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "load_data.hpp"
#include <iomanip>

const int MAXN = 100;
void print_matrix(int N, double A[MAXN][MAXN+1]);
void partial_pivot(double A[MAXN][MAXN+1], int n);
void back_substitute(double A[MAXN][MAXN+1], int n, double x[MAXN]);
void check_precision_gauss(double A[MAXN][MAXN+1], int n, double x[MAXN]);
void solve_linear_equation(FunctionData data);
std::vector<double> solve_linear_equation(std::vector<std::vector<double>> matrix, std::vector<double> x, int N);

#endif