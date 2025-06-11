#include "../include/nonlinear_equations.hpp"

int count_newton = 0;
int count_secant = 0;
int count_bisection = 0;
int count_regula_falsi = 0;

double prim(double (*f)(double), double x){
    return (f(x + EPSILON) - f(x - EPSILON))/(2*EPSILON); 
}

bool value_in_vect(double v, std::vector<double>&vect){
    for(double i : vect){
        if(abs(i - v) <= VAL_DIFF_EPSILON) 
            return true;
    }
    return false;
}

double solve_nonlinear_newton(double (*f)(double), double (*f_prim)(double), double y0){
    double y1 = y0;
    for (int i = 0; i < ITERATION_LIMIT; ++i){
        double f_y0 = f(y0);
        double prim_y0 = f_prim(y0);

        if (std::isnan(f_y0) || std::isnan(prim_y0) || std::isinf(prim_y0)) {
            // std::cerr << "Nieprawidlowa wartosc: f(y0)=" << f_y0 << ", prim=" << prim_y0 << "\n";
            return std::numeric_limits<double>::quiet_NaN();
        }

        if (std::abs(prim_y0) < DERIVATIVE_EPSILON) {
            // prim_y0 = std::copysign(DERIVATIVE_EPSILON, prim_y0);
            std::cerr << "Pochodna zbyt bliska 0.\n";
            return std::numeric_limits<double>::quiet_NaN();
        }   

        // std::cout<< "y0: "<<y0<<"\n";
        // std::cout<<y0<<"\n";
        // std::cout<< "f(y0): "<<f(y0)<<"\n";
        // std::cout<< "f_prim(y0): "<<f_prim(y0)<<"\n";

        double step = -f_y0 / prim_y0;
        if (std::abs(step) > MAX_STEP)
                step = std::copysign(MAX_STEP, step);
        
        y1 = y0 + step;

        if (std::abs(y1 - y0) <= EPSILON){
            return y1;
        }   

        y0 = y1;
    }

    std::cerr << "WARNING: Out of iteration limit\n";
    // return std::numeric_limits<double>::quiet_NaN(); 
    return y0;
}

double solve_nonlinear_newton(double (*f)(double), double y0){
    double y1 = y0;
    for (int i = 0; i < ITERATION_LIMIT; ++i){
        count_newton++;
        double f_y0 = f(y0);
        double prim_y0 = prim(f, y0);
        
        // std::cout<< "y0: "<<y0<<"\n";
        // std::cout<<y0<<"\n";
        // std::cout<< "f(y0): "<<f(y0)<<"\n";
        
        if (std::isnan(f_y0) || std::isinf(f_y0) || std::isnan(prim_y0) || std::isinf(prim_y0)) {
            // std::cerr << "Nieprawidlowa wartosc: f(y0)=" << f_y0 << ", prim=" << prim_y0 << "\n";
            return std::numeric_limits<double>::quiet_NaN();
        }

        if (std::abs(prim_y0) < EPSILON) {
            // std::cerr << "WARNING: Pochodna bliska zeru: prim(y0)=" << prim_y0 << "\n";
            return std::numeric_limits<double>::quiet_NaN();
        }

        y1 = y0 - f_y0 / prim_y0;

        if (std::abs(f(y1)) < EPSILON || std::abs(y1 - y0) < EPSILON) {
            return y1;
        }

        y0 = y1;
    }

    std::cerr << "WARNING: Out of iteration limit\n";
    // return std::numeric_limits<double>::quiet_NaN(); 
    return y0;
}

double solve_nonlinear_secant(double (*f)(double), double y0, double y_p){
    // const double PERTURBATION = 1e-6;

    for (int i = 0; i < ITERATION_LIMIT; ++i){
        count_secant++;
        // std::cout<<y0<<"\n";
        double f_y0 = f(y0);
        double f_yp = f(y_p);

        if (std::isnan(f_y0) || std::isnan(f_yp) || std::isinf(f_y0) || std::isinf(f_yp)) {
            // std::cerr << "Nieprawidłowa wartość funkcji, przesuniecie punktów\n";
            // y0 += PERTURBATION;
            // y_p -= PERTURBATION;
            return std::numeric_limits<double>::quiet_NaN();
            // continue;
        }

        double denom = f_y0 - f_yp;

        if (std::abs(denom) < EPSILON) {
            // std::cerr << "Mianownik zbyt bliski 0, przesuniecie punktów\n";
            // y0 += PERTURBATION;
            // y_p -= PERTURBATION;
            // continue;
            return std::numeric_limits<double>::quiet_NaN();
        }

        double y_n = y0 - f_y0 * (y0 - y_p) / denom;

        if (std::abs(y_n - y0) < EPSILON || std::abs(y_n) < EPSILON){
            return y_n;
        }

        y_p = y0;
        y0 = y_n;
    }

    std::cerr << "WARNING: Out of iteration limit\n";
    return y0;
}

double solve_nonlinear_bisection(double (*f)(double), double a, double b){
    // jesli funkcja nad, badz pod osia
    if(!(f(a) * f(b) < 0)){
        return std::numeric_limits<double>::quiet_NaN();
    }

    double mid;
    while ((b-a) >= EPSILON){
        count_bisection++;
        mid = (a+b)/2;
        // std::cout<<mid<<"\n";

        if (std::abs(f(mid)) < EPSILON)
            break;
        else if (f(mid)*f(a) < 0)
            b = mid;
        else
            a = mid;
    }

    return mid;
}

double solve_nonlinear_regula_falsi(double (*f)(double), double a, double b){
    if(!(f(a) * f(b) < 0)){
        return std::numeric_limits<double>::quiet_NaN();
    }

    double x1;

    for (size_t i = 0; i < ITERATION_LIMIT; i++){ 
        count_regula_falsi++;  
        double f_a = f(a);
        double f_b = f(b);

        if (std::isnan(f_a) || std::isnan(f_b) || std::isinf(f_a) || std::isinf(f_b)) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double denom = f_b - f_a;
        if (std::abs(denom) < EPSILON) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        x1 = (a * f_b - b * f_a) / denom;
        // std::cout<<x1<<"\n";

        if(std::abs(f(x1)) < EPSILON || std::abs(b-a) < EPSILON){
            return x1;
        }

        if(f_a * f(x1) < 0){
            b = x1;
        } else {
            a = x1;
        }
    }
    
    std::cerr << "WARNING: Out of iteration limit\n";
    return x1;
}

std::vector<double> solve_nonlin_eq(double (*f)(double), std::pair<double, double> ab, double step){
    std::vector<double> x0;
    std::vector<double> x_p;

    for (double i = ab.first; i <= ab.second-step; i+=step){
        x_p.push_back(i);
        x0.push_back(i+step);
    }

    std::vector<double> output_regula_falsi;

    for (size_t i = 0; i < x0.size(); i++){
        double out = solve_nonlinear_regula_falsi(f, x_p[i], x0[i]);
        if(!std::isnan(out) && !value_in_vect(out, output_regula_falsi)&& abs(f(out)) < 1000 * EPSILON
                && out >= ab.first && out <= ab.second)
            output_regula_falsi.push_back(out);
        }

    // for (size_t i = 0; i < output_regula_falsi.size(); i++){
    //     std::cout << "REGULA FALSI, " << i+1 << ", "<< output_regula_falsi[i] << ", "<< f(output_regula_falsi[i]) <<"\n";
    // }  

    return output_regula_falsi;
}

