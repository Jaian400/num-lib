#include "integration.hpp"

int test_integration(){
    // function data = load_data("d.txt");
    // FunctionData data = load_data("kwadratury_gr_4.txt");
    // print_input(data);

    int degree = 4;
    std::vector<double> ai = {-2, 0,-5,	-9,	1};
    std::pair<double, double> ab = {-2, 2};

    integrate(ai, ab);

    return 0;
}