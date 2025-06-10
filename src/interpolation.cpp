#include "../include/interpolation.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

double interpolate(std::vector<double> x, std::vector<double> f, int n, double xp) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double l = f[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                l *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        result += l;
    }
    return result;
}

double interpolate(std::vector<double> x, std::vector<double> f, double xp) {
    int n = x.size();
    return interpolate(x, f, n, xp);
}

double interpolate(const FunctionData& data, double userInput, int n) {
    double output = 0.0;

    for (int i = 0; i < n; ++i) {
        double term = data.fx[i];
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                term *= (userInput - data.x[j]) / (data.x[i] - data.x[j]);
            }
        }
        output += term;
    }

    return output;
}

void lagrange_program(int step) {
    FunctionData data0 = load_data("interpolacja_gr_4_ITE 1.txt");
    FunctionData data;

    int n = data0.x.size();

    for (int i = 0; i < n; i += step) {
        data.x.push_back(data0.x[i]);
        data.fx.push_back(data0.fx[i]);
    }

    n = data.x.size();
    double totalError = 0.0;

    for (size_t k = 0; k < data0.x.size(); ++k) {
        double input = data0.x[k];
        double output = interpolate(data, input, n);
        totalError += pow(output - data0.fx[k], 2);
    }

    double avgError = totalError / (data0.x.size() - data.x.size());

    std::cout << "Step: " << std::setw(2) << step
              << " | Nodes: " << std::setw(2) << data.x.size()
              << " | Mean Squared Error: " << std::setprecision(5) << avgError << "\n";
}
