#include "../include/approximation.hpp"
#include "../include/integration.hpp"
#include <iomanip>
#include <fstream>

void verify_approximation(const std::vector<double>& coeffs, double (*f)(double), std::pair<double, double> ab, double tolerance) {
    std::ofstream output_csv("output_test_aprox.csv");
    if (!output_csv.is_open()) {
        std::cerr << "Error, cannot open file\n"; 
        return;
    }

    int N = 20;
    double h = (ab.second - ab.first) / N;
    double error_sum = 0;

    // std::cout << std::setw(15) << "testing x" << 
    //                 std::setw(15) << "precised" << 
    //                 std::setw(15) << "aprox" <<
    //                 std::setw(15) << "error" << "\n";

    for (int i = 0; i <= N; ++i) {
        double x = ab.first + i * h;
        double fx = f(x);
        double ax = calculate_f(coeffs, x);
        double error = std::abs(fx - ax);
        error_sum += error;
        // << std::fixed << std::setprecision(5)
        // std::cout << std::setw(15) << x << 
        //             std::setw(15) << fx << 
        //             std::setw(15) << ax <<
        //             std::setw(15) << error << "\n";

        output_csv << x << 
                    "," << fx << 
                    "," << ax <<
                    "," << error << "\n";
    }

    double mean_error = error_sum / (N+1);
    if(mean_error < tolerance){
        std::cout << "TEST PASSED\n";
    } else {
        std::cout << "TEST FAILED\n";
    }

    output_csv.close();
}

double f0 (double x){
    return sin(x);
}

double f1 (double x){
    return std::exp(x) * std::cos(5 * x) - std::pow(x, 3);
}

void test_approx(){
    std::cout << "--------------------- RUNNING APPROXIMATION TEST -----------------------------" << std::endl;
    std::vector<double> base;
    std::pair<double, double> ab = {-1, 2};
    // std::pair<double, double> ab = {0, M_PI/2};
    for (size_t i = 0; i < 10; i++)
    {
        base.push_back(1);
    }

    std::vector<double> output = approximate(ab, f1);

    // for (double o : output){
    //     std::cout << o << "\n";
    // }
    
    // std::cout << "\nAPPROXIMATION TEST \n";
    verify_approximation(output, f1, ab, 0.001);
}