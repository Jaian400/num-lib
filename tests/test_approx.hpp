#include "../include/approximation.hpp"
#include "../include/integration.hpp"
#include <iomanip>
#include <fstream>

bool verify_approximation(const std::vector<double>& coeffs, double (*f)(double), std::pair<double, double> ab, double tolerance) {
    std::ofstream output_csv("output_test_aprox.csv");
    if (!output_csv.is_open()) {
        std::cerr << "Error, cannot open file\n"; 
        return false;
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

    output_csv.close();

    double mean_error = error_sum / (N+1);
    if(mean_error < tolerance){
        return true;
    } 
    return false;
}

bool test_approx_case1(){
    auto f = [](double x){
        return std::exp(x) * std::cos(5 * x) - std::pow(x, 3);
    };
    std::pair<double, double> ab = {-1, 2};
    std::vector<double> output = approximate(ab, f);

    return verify_approximation(output, f, ab, 0.001);
}

bool test_approx_case2(){
    auto f = [](double x){
        return std::sin(x) - 2*x;
    };
    std::pair<double, double> ab = {-3, 0};
    std::vector<double> output = approximate(ab, f);

    return verify_approximation(output, f, ab, 0.001);
}

void test_approx(){
    std::cout << "--------------------- RUNNING APPROXIMATION TEST -----------------------------" << std::endl;
    std::vector<bool(*)()>cases = {test_approx_case1, test_approx_case2};
    for(int i=0; i<cases.size(); i++){
        if(cases[i]){
            std::cout << "TEST NR " << i+1 << " PASSED\n";
            continue;
        }
        std::cout << "TEST NR " << i+1 << " FAILED\n";
    }
}