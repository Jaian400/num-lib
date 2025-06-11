#include "../include/integration.hpp"

void test_integration(){
    double tolerance = 0.0001;

    std::cout << "RUNNING INTEGRATION TEST\n\n";

    std::vector<double> ai_1 = {-2, 0, 5, 9, 1};
    std::pair<double, double> ab_1 = {-2, 2};
    double output_1_excpected = 472.0/15.0;
    double output_1 = integrate(ai_1, ab_1);

    if(abs(output_1 - output_1_excpected) < tolerance){
        std::cout<<"TEST NR 1 PASSED\n";
    } else {
        std::cout<<"TEST NR 1 FAILED\n";
    }

    std::vector<double> ai_2 = {1, 3, 2, 4, 0};
    std::pair<double, double> ab_2 = {-2, 2};
    double output_2_expected = 44.0/3.0; 
    double output_2 = integrate(ai_2, ab_2);

    if (abs(output_2 - output_2_expected) < tolerance) {
        std::cout << "TEST NR 2 PASSED\n";
    } else {
        std::cout << "TEST NR 2 FAILED\n";
    }

    auto f_3 = [](double x){
        return exp(x - 10) + 2 * x * x;
    };
    std::pair<double, double> ab_3 = {-8, 4};
    double output_3_expected = 384.00248; 
    double output_3 = integrate(f_3, ab_3);

    if (abs(output_3 - output_3_expected) < tolerance) {
        std::cout << "TEST NR 3 PASSED\n";
    } else {
        std::cout << "TEST NR 3 FAILED\n";
    }

    auto f_4 = [](double x){
        return sin(x) + x * x;
    };

    std::pair<double, double> ab_4 = {0, M_PI};
    double output_4_expected = 12.335426;
    double output_4 = integrate(f_4, ab_4);

    if (abs(output_4 - output_4_expected) < tolerance) {
        std::cout << "TEST NR 4 PASSED\n";
    } else {
        std::cout << "TEST NR 4 FAILED\n";
    }
}   