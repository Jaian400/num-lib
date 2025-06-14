#include "../include/approximation.hpp"
#include "../include/integration.hpp"
#include "../include/linear_equations.hpp"
#include <functional>
#include <cmath>
#include <vector>
#include <fstream>

double base_func(double x) {
    return pow(x, counter);
}

double base_times_func(double x) {
    return pow(x, counter) * original_function(x);
}

std::vector<double> approximate(std::pair<double, double> ab, double (*f)(double), int N){
    std::vector<std::vector<double>> matrix(N, std::vector<double>(N));
    std::vector<double>b(N);

    original_function = f;

    for (int i = 0; i < N; i++){
        counter = i;
        for (int j = 0; j < N; j++){
            counter = i + j;
            matrix[i][j] = integrate(base_func, ab, INTEGRATION_N);
        }

        counter = i;
        b[i] = integrate(base_times_func, ab, INTEGRATION_N);
    }

    return solve_lin_eq(matrix, b);
}

// auto basis_product = [i, j](double x) {
            //     return std::pow(x, i + j);
            // };
            // matrix[i][j] = integrate(1000, basis_product, ab);


        // auto f_times_basis = [i, f](double x) {
        //     return std::pow(x, i) * f(x);
        // };
        // b[i] = integrate(1000, f_times_basis, ab);