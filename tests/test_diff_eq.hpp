#include "../include/differential_equation.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

bool test_passed(int N, std::vector<double> result, std::pair<double,double> ab, double (*g) (double), std::string filename, double tolerance){
    std::ofstream output_csv;
    output_csv.open(filename);
    
    double h = (ab.second - ab.first) / N;

    // std::cout << std::fixed << std::setprecision(5);
    // std::cout << std::setw(15) << "x  |"
    //                 << std::setw(15) << "numerical  |" 
    //                 << std::setw(15) << "precisied  |" 
    //                 << std::setw(15) << "error  \n";
    // output_csv << "x" << ","
    //                 << "numerical" << "," 
    //                 <<"precisied" << ","
    //                 << "error" << "\n";
    
    // for (size_t i = 0; i < 60; i++){
    //     std::cout<<"-";
    // }
    // std::cout<<"\n";

    double sum_error_sqr = 0;
    double error_sqr;
    
    for(int i = 0; i <= N; ++i){
        double x = ab.first + i * h;
        double expected = g(x);
        double error = std::abs(result[i] - expected);
        error_sqr = std::pow(result[i] - expected,2);

        sum_error_sqr += error_sqr;

        // if(i != N){
        //    continue; 
        // }
        // std::cout << std::setw(14) << x << "|"
        //             << std::setw(14) << result[i] << "|" 
        //             << std::setw(14) <<expected << "|"
        //             << std::setw(14) << error << "\n";
        
                    output_csv << x << ","
                    << result[i] << "," 
                    <<expected << ","
                    << error << "\n";
    }

    // std::cout<<"Mean error sqr ->" << sum_error_sqr/(N+1) << "\n";

    output_csv.close();

    if(error_sqr < tolerance){
        return true;
    }
    return false;
}

// problem
double f(double x, double y){
    return y;
}

// rozwiazanie
double g(double x){
    return std::exp(x);
}

double alfa = 15 * std::pow(10, -12);

// rownanie
double T(double x, double t){
    return - alfa * std::pow(t, 4);   
}

double T0 = 0;

double T_s(double t){
    return 1 / std::pow(3* alfa * t + T0,1.0/3.0);
}

double beta = 0.5;

double F(double y, double t){
    return - beta * y;
}

double F_s(double t){
    return 1115 * std::exp(-beta * t);
}

void test_euler(){
    // std::pair <double, double> ab = {0, 5};
    // double y0 = 1;
    // int N = 500;

    // std::vector <double> result = solve_diff_eq_euler(N, ab, y0, f);
    
    // if(test_passed(N, result, ab, g)){
    //     std::cout << "Acceptable error\n";
    // } else {
    //     std::cout << "Big error\n";
    // }

    std::pair <double, double> ab = {0, 1115};
    double y0 = 1115;
    T0 = 1 / std::pow(y0, 3);
    int N = 50;

    std::vector <double> result = solve_diff_eq_euler(N, ab, y0, T);

    if(test_passed(N, result, ab, T_s, "output_diff.csv", 0.01)){
        // std::cout << "Acceptable error\n";
    } else {
        // std::cout << "Big error\n";
    }
}

// int n = 10;

void test_method(std::vector<double> (*method)(int, std::pair<double, double>, double, double (*)(double, double)), std::string filename){
    double tolerance = 0.01;
    
    std::pair <double, double> ab = {0, 1115};
    double y0 = 1115;
    T0 = 1 / std::pow(y0, 3);
    int N = 100;

    std::vector <double> result = method(N, ab, y0, T);
    
    if(test_passed(N, result, ab, T_s, filename, tolerance)){
        std::cout << "TEST 1 PASSED\n";
    } else {
        std::cout << "TEST 1 FAILED\n";
    }

    ab = {0, 2000}; 

    result = method(N, ab, y0, T);

    if(test_passed(N, result, ab, T_s, filename, tolerance)){
        std::cout << "TEST 2 PASSED\n";
    } else {
        std::cout << "TEST 2 FAILED\n";
    }

    ab = {0, 10}; 

    result = method(N, ab, y0, F);

    if(test_passed(N, result, ab, F_s, filename, tolerance)){
        std::cout << "TEST WITH WRONG PARAMETERES PASSED\n";
    } else {
        std::cout << "TEST WITH WRONG PARAMETERES FAILED\n";
    }
}

void test_diff_eq(){
    std::cout << "--------------------- RUNNING DIFFERENTIAL EQUATION TEST ---------------------" << std::endl;

    // std::cout<<"TEST EULER-----------------\n\n";
    // test_method(solve_diff_eq_euler, "output_test_euler.csv");
    // std::cout<<"\n\n";

    // std::cout<<"TEST HEUNA-----------------\n\n";
    // test_method(solve_diff_eq_heuna, "output_test_heuna.csv");
    // std::cout<<"\n\n";
    
    // std::cout<<"TEST MIDPOINT-------------------\n\n";
    // test_method(solve_diff_eq_midpoint, "output_test_midpoint.csv");
    // std::cout<<"\n\n";
    
    // std::cout<<"TEST DIFF EQUTAIONS-------------------\n\n";
    test_method(solve_diff_eq_runge_kutty, "output_test_diff_eq.csv");
    // std::cout<<"\n";
}
