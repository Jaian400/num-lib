#include "../include/differential_equation.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

bool test_passed(int N, std::vector<double> result, std::pair<double,double> ab, double (*g) (double), std::string filename){
    std::ofstream output_csv;
    output_csv.open(filename);
    
    double h = (ab.second - ab.first) / N;
    double tolerance = 0.01; // duży krok duży błąd

    // std::cout << std::fixed << std::setprecision(5);
    std::cout << std::setw(15) << "x  |"
                    << std::setw(15) << "numerical  |" 
                    << std::setw(15) << "precisied  |" 
                    << std::setw(15) << "error  \n";
    // output_csv << "x" << ","
    //                 << "numerical" << "," 
    //                 <<"precisied" << ","
    //                 << "error" << "\n";
    
    for (size_t i = 0; i < 60; i++){
        std::cout<<"-";
    }
    std::cout<<"\n";

    double sum_error_sqr = 0;
    
    for(int i = 0; i <= N; ++i){
        double x = ab.first + i * h;
        double expected = g(x);
        double error = std::abs(result[i] - expected);
        double error_sqr = std::pow(result[i] - expected,2);
        sum_error_sqr += error_sqr;

        if(i != N){
           continue; 
        }
        std::cout << std::setw(14) << x << "|"
                    << std::setw(14) << result[i] << "|" 
                    << std::setw(14) <<expected << "|"
                    << std::setw(14) << error << "\n";
        
                    output_csv << x << ","
                    << result[i] << "," 
                    <<expected << ","
                    << error << "\n";
        
        // if(error > tolerance){
        //     std::cout << std::setw(14) << x << "|"
        //             << std::setw(14) << result[i] << "|" 
        //             << std::setw(14) <<expected << "|"
        //             << std::setw(14) << error << "\n";
        //     return false;
        // }
    }

    std::cout<<"Mean error sqr ->" << sum_error_sqr/(N+1) << "\n";

    output_csv.close();

    return true;
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

    // return 1 / (std::pow(3, 1.0/3.0) * std::pow(alfa * t, 1.0/3.0));

    // const double numerator = 446000 * std::pow(5, 2.0/3.0);
    // const double denominator = std::pow(1600000000 - 99806103 * t, 1.0/3.0);
    
    // return numerator / denominator;
}

void test_euler(){
    // std::pair <double, double> ab = {0, 5};
    // double y0 = 1;
    // int N = 500;

    // std::vector <double> result = solve_differential_equation(N, ab, y0, f);
    
    // if(test_passed(N, result, ab, g)){
    //     std::cout << "Acceptable error\n";
    // } else {
    //     std::cout << "Big error\n";
    // }

    std::pair <double, double> ab = {0, 1115};
    double y0 = 1115;
    T0 = 1 / std::pow(y0, 3);
    int N = 50;

    std::vector <double> result = solve_differential_equation(N, ab, y0, T);

    if(test_passed(N, result, ab, T_s, "output_diff.csv")){
        // std::cout << "Acceptable error\n";
    } else {
        // std::cout << "Big error\n";
    }
}

// int n = 10;

void test_method(std::vector<double> (*method)(int, std::pair<double, double>, double, double (*)(double, double)), std::string filename){
    std::pair <double, double> ab = {0, 1115};
    double y0 = 1115;
    T0 = 1 / std::pow(y0, 3);
    int N = 50;

    std::vector <double> result = method(N, ab, y0, T);

    if(test_passed(N, result, ab, T_s, filename)){
        // std::cout << "Acceptable error\n";
    } else {
        // std::cout << "Big error\n";
    }
}

int main(){

    std::cout<<"\n";

    std::cout<<"TEST EULER-----------------\n\n";
    test_method(solve_differential_equation, "output_euler.csv");
    std::cout<<"\n\n";

    std::cout<<"TEST HEUNA-----------------\n\n";
    test_method(solve_heuna, "output_heuna.csv");
    std::cout<<"\n\n";
    
    std::cout<<"TEST MIDPOINT-------------------\n\n";
    test_method(solve_midpoint, "output_midpoint.csv");
    std::cout<<"\n\n";
    
    std::cout<<"TEST RUNGE KUTTY-------------------\n\n";
    test_method(solve_runge_kutty, "output_runge_kutty.csv");
    std::cout<<"\n\n";

    return 0;
}
