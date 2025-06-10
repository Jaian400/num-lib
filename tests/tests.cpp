#include "test_approx.hpp"
#include "test_diff_eq.hpp"
#include "test_nonlin_eq.hpp"
#include "test_lin_eq.hpp"
#include "test_interpolate.hpp"

#include "../examples/example_interpolate.hpp"
#include "../examples/example_solve_diff_eq.hpp"

int main(){
    // test_diff_eq();
    // test_interpolate();
    // test_approx();
    // test_nonlin_eq();
    // test_lin_eq();

    example_interpolate();
    example_solve_diff_eq();

    return 0;
}