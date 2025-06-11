#include "../include/integration.hpp"
#include "math.h"
#include <fstream>

double integrate(std::vector <double> ai, std::pair <double, double> ab, int n){
    double h;
    std::vector <double> x;

    h = (ab.second - ab.first)/(2*n);
    // std::cout<<"h -> " << h<<"\n";
    // std::cout<<"x -> ";
    for (int i = 0; i <= 2*n; i++)
    {
        x.push_back(ab.first + i*h);
        // std::cout<<x[i]<<" ";
    }
    // std::cout<<"\n";

    double output_simpson = h * simpson(ai, x, n) / 3;
    // std::cout<<"Wynik z simpsona -> " << output_simpson << "|";

    return output_simpson;
}

double integrate(double (*f)(double), std::pair <double, double> ab, int n){
    std::vector<double> x = {0.0, 0.5384693, -0.5384693, 0.9061798, -0.9061798};
    std::vector<double> wi = {0.5688889, 0.4786287, 0.4786287, 0.2369269, 0.2369269};
    
    double output_quad = subdivided_quadrature(n, wi, x, ab, f);
    return output_quad;
}

double simpson(double(*f)(double), std::vector <double> x, int n){
    double sum1 = 0.f;
    double sum2 = 0.f;

    for (int i = 1; i <= 2*n - 1; i += 2) {
        sum1 += f(x[i]);
    }

    for (int i = 2; i <= 2*n - 2; i += 2) {
        sum2 += f(x[i]);
    }

    return f(x[0]) + 4 * sum1 + 2 * sum2 + f(x[2*n]);
}

double simpson(std::vector <double> ai, std::vector <double> x, int n){
    double sum1 = 0.f;
    double sum2 = 0.f;

    for (int i = 1; i <= 2*n - 1; i += 2) {
        sum1 += calculate_f(ai, x[i]);
    }

    for (int i = 2; i <= 2*n - 2; i += 2) {
        sum2 += calculate_f(ai, x[i]);
    }

    return calculate_f(ai, x[0]) + 4 * sum1 + 2 * sum2 + calculate_f(ai, x[2*n]);
}

double subdivided_quadrature(int n, std::vector<double> wi, std::vector<double> xi, std::pair<double, double> ab, double (*f)(double)) {
    double total = 0.f;
    double a = ab.first;
    double b = ab.second;
    double h = (b - a) / n;

    for (int i = 0; i < n; ++i) {
        double sub_a = a + i * h;
        double sub_b = sub_a + h;
        total += quadrature(f, xi, wi, {sub_a, sub_b});
    }

    return total;
}

double quadrature(double (*f)(double), std::vector <double> xi, std::vector <double> wi, std::pair <double, double> ab){
    double sum = 0.f;
    for (int i=0; i<int(xi.size()); i++){
        sum += wi[i] * f(((ab.second - ab.first) * xi[i] + (ab.second + ab.first)) * 0.5f);
    }

    return (ab.second-ab.first) * sum / 2;
}

double quadrature(int n, std::vector <double> x, std::vector <double> wi, std::pair <double, double> ab, std::vector <double> ai){
    double sum = 0.f;
    for (int i=0; i<n; i++){
        sum += wi[i] * calculate_f(ai, ((ab.second - ab.first) * x[i] + (ab.second + ab.first)) * 0.5f);
    }

    return (ab.second-ab.first) * sum / 2;
}

double trapezoid(std::vector <double> ai, std::vector <double> x, int n){
    double sum = 0.f;
    for (int i = 1; i < n; i++){
        sum += (x[i] - x[i-1]) * (calculate_f(ai, x[i]) + calculate_f(ai, x[i-1]));
    }

    return 0.5 * sum; 
}

double rectangual(std::vector <double> ai, std::vector <double> x, int n){
    double sum = 0.f;
    for (int i = 1; i < n; i++){
        sum += (x[i] - x[i-1]) * calculate_f(ai, x[i]);
    }

    return sum;
}

double calculate_f(std::vector<double> ai, double x){
    double result = ai.back();
    for (int i = int(ai.size()) - 2; i >= 0; --i) {
        result = result * x + ai[i];
    }
    return result;
}

void print_input(FunctionData data){
    std::cout<<"n -> "<<data.N<<"\n";
    std::cout<<"ai -> ";
    for (int i = 0; i < int(data.x.size()); i++)
    {
        std::cout<<data.x[i]<<" ";
    }
    std::cout<<"\n";
    std::cout<<"a, b -> ";
    for (int i = 0; i < int(data.fx.size()); i++)
    {
        std::cout<<data.fx[i]<<" ";
    }
    std::cout<<"\n\n";
}