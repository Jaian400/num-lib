#include "../include/nonlinear_equations.hpp"

double f1_neq(double x){
    if (x <= -1.0 || x == -3.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return log(x + 1.0) - 1.0 / (x + 3.0);
}
double f1_prim(double x){
    if (x == -3 || x == -1) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return  (1 / (x + 3)*(x+3)) + (1/(x+1));
}

double f2(double x){
    if (x == 0) return std::numeric_limits<double>::quiet_NaN();

    return pow(x, 3) + 30 * cos(x) - 1/x;
}

double f2_prim(double x){
    if (x == 0) return std::numeric_limits<double>::quiet_NaN();

    return 3 * pow(x, 2) - 30 * sin(x) - 1/(x*x);
}

double f3(double x){
    if (x == -2 || x == -4) return std::numeric_limits<double>::quiet_NaN();

    return sin(3 * M_PI * x) / (x+2) + 1/(x+4);
}

double f3_prim(double x){
    if (x == -2 || x == 0) return std::numeric_limits<double>::quiet_NaN();

    return (3 * M_PI * (x+2) * cos(3 * M_PI * x) - sin(3 * M_PI * x))/ std::pow(x + 2, 2) - 1/(pow(x,4));
}

double f4(double x){
    if(x <= -1){
        return std::numeric_limits<double>::quiet_NaN();
    }

    return log10(x+1) - pow(x, 3);
}

double f5(double x){
    return cosh(x) - abs(x) - 0.55;
}

double f6(double x){
    if(x == -1){
        return std::numeric_limits<double>::quiet_NaN();
    }
    return cos(3 * M_PI * x) / (x+1);
}

int test_nonlin_eq_old(){
    std::vector<double(*)(double)> funcs = {f1_neq, f2, f3};
    std::vector<double(*)(double)> prims = {f1_prim, f2_prim, f3_prim};
    std::vector<double> x0;
    std::vector<double> x_p;

    std::pair<double, double> ab = {-3, 4};
    double step = 0.01;
    for (double i = ab.first; i <= ab.second-step; i+=step){
        x_p.push_back(i);
        x0.push_back(i+step);
    }

    std::vector<std::vector<double>> output_secant(3);
    std::vector<std::vector<double>> output_bisection(3);
    std::vector<std::vector<double>> output_newton(3);
    std::vector<std::vector<double>> output_newton_2(3);
    
    for(size_t i=0; i<funcs.size();++i){
        // if(i>0){
        //     ab = {-3, 4};
        //     step = 0.01;
        //     x_p.clear();
        //     x0.clear();
        //     for (double j = ab.first; j < ab.second-step; j+=step){
        //         x_p.push_back(j);
        //         x0.push_back(j+step);
        //     }
        // }
        // output_newton[i] = solve_nonlinear_newton(funcs[i], prims[i], x0[i]);
        // std::cout<<"WYNIK NEWTON DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[i] <<" => " << output_newton[i]<<"\n";
        for (size_t j = 0; j < x0.size(); j++){
            double out = solve_nonlinear_newton(funcs[i], prims[i], x_p[j]);
            // std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out << "\n";
            if(!std::isnan(out) && !value_in_vect(out, output_newton[i]))
                output_newton[i].push_back(out);
        }

        for (size_t j = 0; j < output_newton[i].size(); j++){
            std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " -> NEWTON Z PRIM NR " << j+1 << ": "<< output_newton[i][j] <<"\n";
        }

        for (size_t j = 0; j < x0.size(); j++){
            double out = solve_nonlinear_newton(funcs[i], x_p[j]);
            // std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out << "\n";
            if(!std::isnan(out) && !value_in_vect(out, output_newton_2[i]))
                output_newton_2[i].push_back(out);
        }

        for (size_t j = 0; j < output_newton_2[i].size(); j++){
            std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " -> NEWTON BEZ PRIM NR " << j+1 << ": "<< output_newton_2[i][j] <<"\n";
        }

        continue;

        for (size_t j = 0; j < x0.size(); j++){
            double out = solve_nonlinear_secant(funcs[i], x0[j], x_p[j]);
            // std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out << "\n";
            if(!std::isnan(out) && !value_in_vect(out, output_secant[i]))
                output_secant[i].push_back(out);
        }

        for (size_t j = 0; j < output_secant[i].size(); j++){
            std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " -> SECANT NR " << j+1 << ": "<< output_secant[i][j] <<"\n";
        }
        
        // for (size_t j = 0; j < x0.size(); j++){
        //     double out = solve_nonlinear_newton(funcs[i], prims[i], x0[j]);
        //     std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out;
        //     output_newton[i].push_back(out);
        //     output_secant[i] = solve_nonlinear_secant(funcs[i], x0[i], x_p[i]);
        //     std::cout<<"WYNIK SECANT DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x_p[i] << ", "<< x0[i] <<" => " << output_secant[i]<<"\n";
        // }
        
        // ab = {-0.99, 4};
        // step = 1;
        // x0.clear();
        // x_p.clear();
        // for (double k = ab.first; k < ab.second; k+=step){
        //     x_p.push_back(k);
        //     x0.push_back(k+step);
        // }

        // for (size_t j = 0; j < x0.size(); j++){
        //     double out = solve_nonlinear_bisection(funcs[i], x_p[j], x0[j]);
        //     // std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out << "\n";
        //     if(!value_in_vect(out, output_bisection[i]))
        //         output_bisection[i].push_back(out);
        // }

        // for (size_t j = 0; j < output_bisection[i].size(); j++){
        //     std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " -> BISECTION NR " << j+1 << ": "<< output_bisection[i][j] <<"\n";
        // }

        double out = solve_nonlinear_bisection(funcs[i], -3, 4);
        std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " -> BISECTION: " << out <<"\n";

    }

    return 0;
}

void test_secant(){
    std::vector<double> x0;
    std::vector<double> x_p; 
    std::vector<double> output_secant;
    std::pair<double, double> ab = {-3, 4};
    double step = 0.01;
    for (double i = ab.first; i < ab.second-step; i+=step){
        x_p.push_back(i);
        // std::cout<<i<<"\n";
        x0.push_back(i+step);
        // std::cout<<i+step<<"\n";
    }

    // solve_nonlinear_secant(f2, -1.96752e-14, -0.01);
    // solve_nonlinear_secant(f2, 0, -0.01);
    // return;

    // for(size_t i=0;i<x0.size();i++){
    //     std::cout<< x0[i]<< ", " << x_p[i] << "\n";
    // }
    // return;

    for(size_t i=0;i<x0.size();i++){
        double out = solve_nonlinear_secant(f2, x0[i], x_p[i]);
        if(!std::isnan(out) &&!value_in_vect(out, output_secant) && abs(f2(out)) < 1000 * EPSILON
                && out >= ab.first && out <= ab.second){
            output_secant.push_back(out);
            std::cout<<out<<"\n";
            std::cout<<f2(out) << "\n\n";
        }     
    } 
    
}

void test_third(){
    std::vector<double> x0;
    std::vector<double> x_p;

    std::pair<double, double> ab = {-3, 4};
    double step = 0.01;
    for (double i = ab.first; i <= ab.second; i+=step){
        x_p.push_back(i);
        x0.push_back(i+step);
    }

    std::vector<double> output_newton;
    std::vector<double> output_newton_2;

    for (size_t j = 0; j < x0.size(); j++){
            double out = solve_nonlinear_newton(f3, f3_prim, x_p[j]);
            // std::cout<<"WYNIK DLA FUNKCJI NR 3 W OTOCZENIU " << x0[j] <<" => " << out << "\n";
            if(!std::isnan(out) && !value_in_vect(out, output_newton) && abs(f3(out)) < 1000 * EPSILON
                && out >= ab.first && out <= ab.second)
                output_newton.push_back(out);
        }
    
    std::sort(output_newton.begin(), output_newton.end());
    for (size_t j = 0; j < output_newton.size(); j++){
            std::cout<<"WYNIK DLA FUNKCJI NR 3 -> NEWTON Z PRIM NR " << j+1 << ": "<< output_newton[j] <<"| WARTOSC: "<< f3(output_newton[j])<<"\n";
        }

    for (size_t j = 0; j < x0.size(); j++){
            double out = solve_nonlinear_newton(f3, x_p[j]);
            // std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out << "\n";
            if(!std::isnan(out) && !value_in_vect(out, output_newton_2) && abs(f3(out)) < 1000 * EPSILON
                && out >= ab.first && out <= ab.second)
                output_newton_2.push_back(out);
    }

    std::sort(output_newton_2.begin(), output_newton_2.end());
    for (size_t j = 0; j < output_newton_2.size(); j++){
            std::cout<<"WYNIK DLA FUNKCJI NR 3 -> NEWTON BEZ PRIM NR " << j+1 << ": "<< output_newton_2[j] <<"| WARTOSC: "<< f3(output_newton_2[j]) <<"\n";
    }

    if (output_newton_2.size() != output_newton.size()){
        std::cout<<"Nie zwracaja tej samej liczby pierwiastkow\n";
        return;
    }

    std::cout<<"PORÓWNANIE WARTOŚCI Z POCHODNYMI ANALITYCZNYMI Z WYLICZANYMI\n";
    for (size_t i = 0; i < output_newton_2.size(); i++){
        std::cout<<i <<" => " << abs(output_newton[i]-output_newton_2[i])<<"\n";
    }
}

void test_bis(double (*f)(double)){
    std::pair<double, double> ab = {-3, 4};
    std::vector<double> x0;
    std::vector<double> x_p;

    double step = 0.01;
    for (double i = ab.first; i <= ab.second-step; i+=step){
        x_p.push_back(i);
        x0.push_back(i+step);
    }
    std::vector<double> output_bisection;

    for (size_t i = 0; i < x0.size(); i++){
        double out = solve_nonlinear_bisection(f, x0[i], x_p[i]);
        // std::cout<<"WYNIK DLA FUNKCJI NR " << i+1 << " W OTOCZENIU " << x0[j] <<" => " << out << "\n";
        if(!std::isnan(out) && !value_in_vect(out, output_bisection)&& abs(f(out)) < 1000 * EPSILON
                && out >= ab.first && out <= ab.second)
            output_bisection.push_back(out);
        }

    for (size_t i = 0; i < output_bisection.size(); i++){
        std::cout << "BISEKCJA, " << i+1 << ", "<< output_bisection[i] <<"\n";
    }  
}

void test_nonlin_eq_2(double tolerance){
    // std::vector<double(*)(double)> funcs = {f1_neq, f2, f3};
    // std::pair<double, double> ab = {-3, 4};

    double error_sum = 0;
    int count = 0;

    std::vector<double(*)(double)> funcs = {f1_neq, f2, f3, f4, f5, f6};

    std::vector<std::vector<double>> outputs_excepted;
    outputs_excepted.push_back({0.348077}); // 1
    outputs_excepted.push_back({-1.48417,0.03333518,1.72233}); // 2
    outputs_excepted.push_back({-2.61753, -2.35654, -1.65084, -1.35934, -0.963027, -0.709429, -0.282375, -0.054708, 
        0.394475, 0.602896, 1.069, 1.26239, 1.74198, 1.92319, 2.41386, 2.58495}); // 3
    outputs_excepted.push_back({7.58E-17, 0.850651}); // 4
    outputs_excepted.push_back({-1.03427, -0.722765, 0.722765, 1.03427}); // 5
    outputs_excepted.push_back({-2.83333, -2.5, -2.16667, -1.83333, -1.5, -1.16667, -0.833333, -0.5, -0.166667, 
        0.166667, 0.5, 0.833333, 1.16667, 1.5, 1.83333, 2.16667, 2.5, 2.83333}); // 6

    std::pair<double, double> ab = {-3, 3};
    std::vector<std::vector<double>> outputs;

    for (size_t i=0;i<funcs.size();i++){
        std::cout<<"\nTESTY DLA FUNKCJI NUMER "<< i+1 << "\n\n";
        outputs.push_back(solve_nonlin_eq(funcs[i],ab));

        if(outputs[i].size() != outputs_excepted[i].size()){
            std::cout<<"TEST FAILED, num of roots of func "<< i+1 << "\n";
            std::cout<<"Excpected: " << outputs_excepted[i].size() << ", got: " << outputs[i].size() << "\n";
            return;
        }

        std::cout<<"Uzyskane wyniki:\n";
        for (size_t j= 0; j < outputs[i].size(); j++){
            std::cout<<outputs[i][j]<<"\n";
            error_sum += abs(outputs[i][j] - outputs_excepted[i][j]);
            count++;
        }
    }

    double mean_error = error_sum / count;

    if(mean_error < tolerance){
        std::cout<<"TEST PASSED\n";
    } else {
        std::cout<<"TEST FAILED\n";
    }
}

// void generate_points(){
//     std::ofstream out_file("nlin_graphs.csv");
//     for (double i = -3; i < 4; i+=0.01){
//         out_file << i <<","<< f1_neq(i)<<","
//                 << f2(i)<<","
//                 << f3(i)<<"\n";
//     }
//     out_file.close();
// }

// void method_steps(double(*f)(double)){
//     std::cout<<"\nBisekcja\n";
//     solve_nonlinear_bisection(f, 1.06, 1.07);
//     std::cout<<"\nNewton\n";
//     solve_nonlinear_newton(f, 1.06);
//     std::cout<<"\nSieczne\n";
//     solve_nonlinear_secant(f, 1.07, 1.06);
// }

// void test_regula_falsi(){
//     std::vector<double(*)(double)> funcs = {f4, f5, f6};
//     std::pair<double, double> ab = {-3, 3};

//     solve_nonlinear_regula_falsi(f4, -3, 3);
// }

void test_nonlin_eq(){
    std::cout << "--------------------- RUNNING NONLINEAR EQUATION TEST ------------------------" << std::endl;
    // std::cout << "f3(0) = " << f3(0.0) << std::endl;
    // return 0;
    // test_nonlin_eq();
    // test_secant();
    // test_third();
    // double v = solve_nonlinear_newton(f3, f3_prim, -0.1);
    // std::cout<<v << " | Wartosc: "<<f3(v);
    // generate_points();
    // return 0;
    // method_steps(f3);

    double tolerance = 0.01;
    test_nonlin_eq_2(tolerance);
    // std::cout<<"Calkowita liczba wykonanych petli dla metody Newtona -> " << count_newton << "\n";
    // std::cout<<"Calkowita liczba wykonanych petli dla metody siecznych -> " << count_secant << "\n";
    // std::cout<<"Calkowita liczba wykonanych petli dla metody bisekcji -> " << count_bisection << "\n";
    // std::cout<<"Calkowita liczba wykonanych petli dla metody falszywej linii -> " << count_regula_falsi << "\n";

    // test_regula_falsi();
}