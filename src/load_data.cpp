#include "../include/load_data.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

FunctionData load_data(const std::string& filename) {
    std::ifstream inputFile(filename);
    FunctionData func;
    std::string line;

    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return func;
    }

    getline(inputFile, line);
    getline(inputFile, line);
    std::istringstream ss_x(line.substr(4));
    double value;
    while (ss_x >> value) {
        func.x.push_back(value);
    }

    getline(inputFile, line);
    std::istringstream ss_fx(line.substr(6));
    while (ss_fx >> value) {
        func.fx.push_back(value);
    }

    return func;
}

void print_table(const FunctionData& func) {
    std::cout << "\n---------------------------------\n";
    std::cout << "|     x     |    f(x)           |\n";
    std::cout << "---------------------------------\n";

    std::ofstream outputFile("table.csv");

    for (size_t i = 0; i < func.x.size(); ++i) {
        std::cout << "| " << std::setw(8) << func.x[i] 
                  << " | " << std::setw(14) << func.fx[i] << " |\n";
        outputFile << func.x[i] << "\t" << func.fx[i] << "\n";
    }

    outputFile.close();
    std::cout << "---------------------------------\n";
}
