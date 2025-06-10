#include "../include/lu.hpp"
#include <math.h>
#include <string.h>
#include <iomanip>

// A, B multiplied matrixes; C output
void multiply_matrices(int N, double A[MAXN][MAXN+1], double B[MAXN][MAXN+1], double C[MAXN][MAXN+1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void create_matrixes(int N, double A[MAXN][MAXN+1], double L[MAXN][MAXN+1], double U[MAXN][MAXN+1]){
    for (int i=0; i<N;i++){
        for (int k=0; k<N;k++){
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        for (int k=0; k<N;k++){
            if(i==k){
                L[i][k]=1;
                continue;
            }   

            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[k][j] * U[j][i];
            }
            L[k][i] = (A[k][i] - sum) / U[i][i];
        }

        std::cout<<"Macierz L w iteracji nr "<< i + 1 << ":\n";
        print_matrix(N, L);
        std::cout<<"Macierz U w iteracji nr "<< i + 1 << ":\n";
        print_matrix(N, U);
    }

    // for (int i=0; i<N;i++){
    //     for (int j=0; j<N+1; j++){
    //         L[i][j] = U[j][i];
    //     }
    // }
}

// L * z = b
void forward_substitution(int N, double L[MAXN][MAXN+1], double b[MAXN], double z[MAXN]) {
    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * z[j];
        }
        z[i] = (b[i] - sum);
    }
}

// U * x = z
void backward_substitution(int N, double U[MAXN][MAXN+1], double z[MAXN], double x[MAXN]) {
    for (int i = N - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < N; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / U[i][i];
    }
}

void check_precision_lu(double A[MAXN][MAXN+1], int n, double x[MAXN]) {
    std::cout << "Sprawdzanie dokladnosci rozwiazania:\n";
    
    for (int i = 0; i < n; i++) {
        double computed_b = 0.0;
        
        for (int j = 0; j < n; j++) {
            computed_b += A[i][j] * x[j]; 
        }
        
        double original_b = A[i][n]; 
        double error = fabs(computed_b - original_b);

        std::cout << "Obliczone = " << std::setw(4)<<computed_b 
                  << " | Oczekiwane = " << std::setw(4)<<original_b 
                  << " | Blad = " << error << "\n";
    }
}

