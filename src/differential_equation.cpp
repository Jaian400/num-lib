#include "../include/differential_equation.hpp"

std::vector <double> solve_diff_eq(std::pair <double, double> ab, double y0, double (*f)(double, double), int N){
    return solve_diff_eq_runge_kutty(N, ab, y0, f);
}

std::vector<double> solve_diff_eq_euler(int N, std::pair<double, double> ab, double y0, double (*f)(double, double)){
    double x0 = ab.first;
    double h = (ab.second - ab.first) / N;

    std::vector <double> out (N + 1);
    out[0] = y0;

    double x = x0;
    double y = y0;
    for (int i = 1; i <= N; ++i) {
        x = x + h;
        y = y + h * f(x, y);
        out[i] = y;
    }

    return out;
}

std::vector<std::pair<double, double>> solve_differential_equation_with_x(int N, std::pair<double, double> ab, double y0, double (*f)(double, double)){
    double x0 = ab.first;
    double h = (ab.second - ab.first) / N;

    std::vector<std::pair<double, double>> out(N + 1);
    out[0] = {x0, y0};

    double x = x0;
    double y = y0;
    for (int i = 1; i <= N; ++i) {
        x = x + h;
        y = y + h * f(x, y);
        out[i] = {x, y};
    }

    return out;
}

std::vector<double> solve_diff_eq_heuna(int N, std::pair<double, double> ab, double y0, double (*f)(double, double)){
    double h = (ab.second - ab.first) / N;

    std::vector <double> out (N + 1);
    out[0] = y0;

    for (int i = 0; i < N; ++i) {
        double x = ab.first + i * h;
        double y_= out[i] + h * f(x, out[i]);
        out[i + 1] = out[i] + h / 2 * (f(x, out[i]) + f(x + h, y_));
    }

    return out;
}

std::vector<double> solve_diff_eq_midpoint(int N, std::pair<double, double> ab, double y0, double (*f)(double, double)){
    double h = (ab.second - ab.first) / N;
    std::vector <double> out (N + 1);
    out[0] = y0;

    for (int i = 0; i < N; ++i) {
        double x = ab.first + i * h;
        double f_ = f(x + h / 2, out[i] + h / 2 * f(x, out[i]));
        out[i + 1] = out[i] + h * f_;
    }
    return out;
}

std::vector<double> solve_diff_eq_runge_kutty(int N, std::pair<double, double> ab, double y0, double (*f)(double, double)){
    double h = (ab.second - ab.first) / N;
    std::vector <double> out (N + 1);
    out[0] = y0;
    for (int i = 0; i < N; ++i) {
        double xi = ab.first + i * h;
        double k1 = h * f(xi, out[i]);
        double k2 = h * f(xi + h / 2, out[i] + k1 / 2);
        double k3 = h * f(xi + h / 2, out[i] + k2 / 2);
        double k4 = h * f(xi + h, out[i] + k3);
        out[i + 1] = out[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
    }
    return out;
}
