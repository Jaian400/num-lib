#include "integration.hpp"

int test_integration(){
    // function data = load_data("d.txt");
    FunctionData data = load_data("kwadratury_gr_4.txt");
    print_input(data);

    int degree = data.N; 
    std::vector<double> ai = data.x;
    std::pair<double, double> ab = {data.fx[0], data.fx[1]};
    // std::pair<double, double> ab = {3.5, 6.5296812439344};

    for (size_t i = 10; i < 100; i++)
    {
        integrate(i, ai, ab);
    }

    return 0;
}