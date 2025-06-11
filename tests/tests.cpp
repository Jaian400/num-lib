#include "test_approx.hpp"
#include "test_diff_eq.hpp"
#include "test_nonlin_eq.hpp"
#include "test_lin_eq.hpp"
#include "test_interpolate.hpp"
#include "test_integration.hpp"

#include "../examples/example_interpolate.hpp"
#include "../examples/example_solve_diff_eq.hpp"

int main(){
    std::cout << "--------------------- RUNNING DIFFERENTIAL EQUATION TEST ---------------------" << std::endl;
    test_diff_eq();
    std::cout << "--------------------- RUNNING INTERPOLATION TEST -----------------------------" << std::endl;
    test_interpolate();
    std::cout << "--------------------- RUNNING APPROXIMATION TEST -----------------------------" << std::endl;
    test_approx();
    std::cout << "--------------------- RUNNING NONLINEAR EQUATION TEST ------------------------" << std::endl;
    test_nonlin_eq();    
    std::cout << "--------------------- RUNNING LINEAR EQUATION SYSTEM TEST --------------------" << std::endl;
    test_lin_eq();

    // example_interpolate();
    // example_solve_diff_eq();
    test_integration();

    return 0;
}