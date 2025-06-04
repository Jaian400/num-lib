#include "../include/approximation.hpp"
#include "../include/integration.hpp"
#include "../include/gauss.hpp"
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

std::vector<double> approximate(std::vector <double>base, std::pair<double, double> ab, double (*f)(double)){
    int N = base.size();
    std::vector<std::vector<double>> matrix(N, std::vector<double>(N));
    std::vector<double>b(N);

    original_function = f;

    for (size_t i = 0; i < N; i++){
        counter = i;
        for (size_t j = 0; j < N; j++){
            counter = i + j;
            matrix[i][j] = integrate(INTEGRATION_N, base_func, ab);
        }

        counter = i;
        b[i] = integrate(INTEGRATION_N, base_times_func, ab);
    }

    return solve_linear_equation(matrix, b, N);
}

// auto basis_product = [i, j](double x) {
            //     return std::pow(x, i + j);
            // };
            // matrix[i][j] = integrate(1000, basis_product, ab);


        // auto f_times_basis = [i, f](double x) {
        //     return std::pow(x, i) * f(x);
        // };
        // b[i] = integrate(1000, f_times_basis, ab);