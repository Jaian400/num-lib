#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "test_approx.hpp"
#include "test_diff_eq.hpp"
#include "test_nonlin_eq.hpp"
#include "test_lin_eq.hpp"
#include "test_interpolate.hpp"
#include "test_integration.hpp"

#include "../examples/example_interpolate.hpp"
#include "../examples/example_solve_diff_eq.hpp"


void print_usage(const std::map<std::string, std::function<void()>>& tests) {
    std::cerr << "Usage: make run TEST=<function_name>" << std::endl;
    std::cerr << "Available functions:" << std::endl;
    for (const auto& pair : tests) {
        std::cerr << "  " << pair.first << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::map<std::string, std::function<void()>> tests;

    tests["diff_eq"] = [](){
        test_diff_eq();
    };
    tests["interpolate"] = [](){
        test_interpolate();
    };
    tests["approx"] = [](){
        test_approx();
    };
    tests["nonlin_eq"] = [](){
        test_nonlin_eq();
    };
    tests["lin_eq"] = [](){
        test_lin_eq();
    };
    tests["integration"] = [](){
        test_integration();
    };
    tests["ex_interpolate"] = [](){
        example_interpolate();
    };
    tests["ex_diff_eq"] = [](){
        example_solve_diff_eq();
    };
    tests["all"] = [](){
        std::cout << "--------------------- RUNNING ALL TESTS --------------------------------------" << std::endl;
        test_diff_eq();        
        test_interpolate();
        test_approx();
        test_nonlin_eq();
        test_lin_eq();
        test_integration();
    };

    if (argc != 2) {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        print_usage(tests);
        return 1; 
    }

    std::string test_name = argv[1];
    auto it = tests.find(test_name);

    if (it != tests.end()) {
        it->second(); 
    } else {
        std::cerr << "Error: Test '" << test_name << "' not found." << std::endl;
        print_usage(tests);
        return 1;
    }

    return 0;
}