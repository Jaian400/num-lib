#include "../include/gauss.hpp"
#include <math.h>

void print_matrix(int N, double A[MAXN][MAXN+1]){
    for(int i = 0; i < N;i++){
        for (int j = 0; j < N+1; j++)
        {
            std::cout<<A[i][j]<< "\t";\
        }
        std::cout<<"\n";
    }
}

void partial_pivot(double A[MAXN][MAXN+1], int n) {
    for (int i = 0; i < n; i++) {
        int pivot_row = i;
        for (int j = i+1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot_row][i])) {
                pivot_row = j;
            }
        }
        if (pivot_row != i) {
            for (int j = i; j <= n; j++) {
                std::swap(A[i][j], A[pivot_row][j]);
            }
        }
        for (int j = i+1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k <= n; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }

        // print_matrix(n, A);
        // std::cout<<"\n\n";
    }
}

void back_substitute(double A[MAXN][MAXN+1], int n, double x[MAXN]) {
    for (int i = n-1; i >= 0; i--) {
        double sum = 0;
        for (int j = i+1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (A[i][n] - sum) / A[i][i];
    }
}

void check_precision(double A[MAXN][MAXN+1], int n, double x[MAXN]) {
    std::cout << "\nSprawdzanie dokladnosci rozwiazania:\n";
    
    for (int i = 0; i < n; i++) {
        double computed_b = 0.0;
        
        for (int j = 0; j < n; j++) {
            computed_b += A[i][j] * x[j]; 
        }
        
        double original_b = A[i][n]; 
        double error = fabs(computed_b - original_b);

        std::cout << "Obliczone = " << std::setw(4)<<computed_b 
                  << ", Oczekiwane = " << std::setw(4)<<original_b 
                  << ", Blad = " << error << "\n";
    }
}

void solve_linear_equation(FunctionData data){
    int N = data.x.size();
    double A[MAXN][MAXN+1];
    double A_prim[MAXN][MAXN+1];
    double x[MAXN];
    
    int count = 0;
    for(int i = 0; i < N;i++){
        for (int j = 0; j < N; j++)
        {
            A[i][j] = data.fx[count];
            A_prim[i][j] = data.fx[count];
            count++;
        }
        A[i][N] = data.x[i];
        A_prim[i][N] = data.x[i];
    }

    // print_matrix(N, A);
    // std::cout<<"\n\n\n";

    partial_pivot(A, N);
    back_substitute(A, N, x);
    
    std::cout << "Rozwiazania: \n";
    for (int i = 0; i < N; i++) {
      
        std::cout << x[i] << "\n";
    }

    check_precision(A_prim, N, x);
}

std::vector<double> solve_linear_equation(std::vector<std::vector<double>> matrix, std::vector<double> b, int N){
    double A[MAXN][MAXN+1];
    double A_prim[MAXN][MAXN+1];
    double x[MAXN];
    std::vector<double> output;
    
    for(int i = 0; i < N;i++){
        for (int j = 0; j < N; j++)
        {
            A[i][j] = matrix[i][j];
            A_prim[i][j] =  matrix[i][j];
        }
        A[i][N] = b[i];
        A_prim[i][N] = b[i];
    }

    // print_matrix(N, A);
    // std::cout<<"\n\n\n";

    partial_pivot(A, N);
    back_substitute(A, N, x);
    
    // std::cout << "Rozwiazania: \n";
    for (int i = 0; i < N; i++) {
      
        // std::cout << x[i] << "\n";
        output.push_back(x[i]);
    }

    return output;
}

// int main(){
//     FunctionData data = load_data("gauss_elimination_gr4_A.txt");
    
//     // std::vector <float> b = data.x;
//     // std::vector <std::vector<float>> A(N, std::vector<float>(N));

//     return 0;
// }
