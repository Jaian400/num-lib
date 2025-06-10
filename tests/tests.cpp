#include "test_approx.hpp"
#include "test_diff_eq.hpp"
#include "test_nonlin_eq.hpp"
#include "test_interpolate.hpp"

int main(){
    // test_diff_eq();
    test_interpolate();
    // test_approx();
    test_nonlin_eq();

    return 0;
}