double func_decay(double x, double y) {
    // y' = -0.5 * y (radioactive decay model)
    return -0.5 * y;
}

void example_solve_diff_eq(){
    std::cout << "--- Example: Solving differential equations (solve_diff_eq) ---" << std::endl;
    std::cout << "Modeling the decay of a substance, where the decay rate is proportional to the amount of substance (y' = -0.5*y)." << std::endl;
    double initial_amount = 100.0;
    int steps = 10;
    std::pair<double, double> time_interval = {0.0, 5.0};
    
    std::cout << "Initial condition: y(0) = " << initial_amount << std::endl;
    std::cout << "Time interval: [" << time_interval.first << ", " << time_interval.second << "], Number of steps: " << steps << std::endl;

    std::vector<double> decay_results = solve_diff_eq(time_interval, initial_amount, func_decay, steps);
    
    std::cout << "\nAmount of substance at subsequent time points:" << std::endl;
    for (size_t i = 0; i < decay_results.size(); ++i) {
        double current_time = time_interval.first + i * (time_interval.second - time_interval.first) / steps;
        std::cout << "t = " << std::setw(4) << current_time << "s,  y(t) = " << decay_results[i] << std::endl;
    }
    std::cout << "--------------------------------------------------\n" << std::endl;
}