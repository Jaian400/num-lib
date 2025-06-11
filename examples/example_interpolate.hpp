void example_interpolate(){
    std::cout << "--------------------- RUNNING INTERPOLATION EXAMPLE --------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- Example: Interpolation (interpolate) ---" << std::endl;
    std::cout << "This example interpolates a temperature value based on a given set of measurements." << std::endl;
    std::vector<double> hours = {0.0, 2.0, 4.0, 6.0};
    std::vector<double> temps = {15.0, 19.0, 18.0, 22.0};
    double hour_to_check = 3.5;

    std::cout << "Input data (hours): ";
    for(double h : hours) std::cout << h << "h ";
    std::cout << std::endl;
    
    std::cout << "Input data (temperatures): ";
    for(double t : temps) std::cout << t << "C ";
    std::cout << std::endl;

    double interpolated_temp = interpolate(hours, temps, hours.size(), hour_to_check);
    std::cout << "\nEstimated temperature at hour " << hour_to_check << " is: " << interpolated_temp << " C" << std::endl;
    std::cout << "--------------------------------------------------\n" << std::endl;
}
