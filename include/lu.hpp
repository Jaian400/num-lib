#ifndef LU_HPP
#define LU_HPP

#include "load_data.hpp"
#include "gauss.hpp"

void multiply_matrices(int N, double A[MAXN][MAXN+1], double B[MAXN][MAXN+1], double C[MAXN][MAXN+1]);
void create_matrixes(int N, double A[MAXN][MAXN+1], double L[MAXN][MAXN+1], double U[MAXN][MAXN+1]);
void forward_substitution(int N, double L[MAXN][MAXN+1], double b[MAXN], double z[MAXN]);
void backward_substitution(int N, double U[MAXN][MAXN+1], double z[MAXN], double x[MAXN]);
void check_precision_lu(double A[MAXN][MAXN+1], int n, double x[MAXN]);

#endif
