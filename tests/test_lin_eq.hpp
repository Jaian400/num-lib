#include "../include/gauss.hpp"
#include <iostream>
#include <math.h>

bool compare_vectors(const std::vector<double>& result, const std::vector<double>& expected) {
    const double epsilon = 1e-9;
    if (result.size() != expected.size()) {
        return false;
    }
    for (size_t i = 0; i < result.size(); ++i) {
        if (std::fabs(result[i] - expected[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

void run_test(const std::string& test_name, 
              const std::vector<std::vector<double>>& A, 
              const std::vector<double>& b, 
              const std::vector<double>& expected_x) {
                  
    std::cout << "Running test: " << test_name << "..." << std::endl;
    
    std::vector<double> actual_x = solve_lin_eq(A, b);

    if (compare_vectors(actual_x, expected_x)) {
        std::cout << "[ PASS ]" << std::endl;
    } else {
        std::cout << "[ FAIL ]" << std::endl;
        std::cout << "  Expected: { ";
        for(const auto& val : expected_x) std::cout << val << " ";
        std::cout << "}" << std::endl;
        std::cout << "  Actual:  { ";
        for(const auto& val : actual_x) std::cout << val << " ";
        std::cout << "}" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

/**
 * Test 1:
 * 2x + y + z = 5
 * 4x - 6y     = -2
 * -2x + 7y + 2z = 9
 */
void test_3x3() {
    std::vector<std::vector<double>> A = {
        {2, 1, 1},
        {4, -6, 0},
        {-2, 7, 2}
    };
    std::vector<double> b = {5, -2, 9};
    std::vector<double> expected_x = {1.0, 1.0, 2.0};
    
    run_test("Simple 3x3 sysytem", A, b, expected_x);
}

/**
 * Test 2:
 *     y + z + w = 6
 * 2x + y - z + 2w = 5
 *  x + 2y + 3z - w = 5
 * 3x - y - 2z + 4w = 11
 */
void test_4x4() {
    std::vector<std::vector<double>> A = {
        {0, 1, 1, 1},
        {2, 1, -1, 2},
        {1, 2, 3, -1},
        {3, -1, -2, 4}
    };
    std::vector<double> b = {6, 5, 5, 11};
    std::vector<double> expected_x = {5.0/7.0, -4.0/7.0, 3.0, 25.0/7.0};
    
    run_test("4x4 sysytem that needs pivoting", A, b, expected_x);
}

void test_lin_eq(){
    test_3x3();
    test_4x4();
}