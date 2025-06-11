#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "load_data.hpp"
#include <iomanip>

const int MAXN = 100;
void print_matrix(int N, double A[MAXN][MAXN+1]);
void partial_pivot(double A[MAXN][MAXN+1], int n);
void back_substitute(double A[MAXN][MAXN+1], int n, double x[MAXN]);
void check_precision_gauss(double A[MAXN][MAXN+1], int n, double x[MAXN]);
void solve_lin_eq(FunctionData data);
std::vector<double> solve_lin_eq(const std::vector<std::vector<double>>& matrix,const std::vector<double>& b);
#endif