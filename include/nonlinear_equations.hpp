#ifndef NONLINEAR_EQUATIONS_HPP
#define NONLINEAR_EQUATIONS_HPP
#include "math.h"
#include <vector>
#include <iostream>
#include <cmath> //td::isnan, std::isinf
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
/*
Założenia:

    1. W przedziale [ a , b ] {\displaystyle [a,b]} znajduje się dokładnie jeden pierwiastek funkcji f . {\displaystyle f.}
    2. Funkcja ma różne znaki na krańcach przedziału, tj. f ( a ) ⋅ f ( b ) < 0. {\displaystyle f(a)\cdot f(b)<0.}
    3. Pierwsza i druga pochodna funkcji mają stały znak w tym przedziale.
*/
// f - function to solve, y0 - value of function in y0
double solve_nonlinear_newton(double (*f)(double), double(*f_prim)(double), double y0);
double solve_nonlinear_newton(double (*f)(double), double y0);
double solve_nonlinear_secant(double (*f)(double), double y0, double y_p);
double solve_nonlinear_bisection(double (*f)(double), double a, double b);
double solve_nonlinear_regula_falsi(double (*f)(double), double a, double b);

std::vector<double> solve_nonlin_eq(double (*f)(double), std::pair<double, double> ab);
std::vector<double> solve_nonlin_eq(double (*f)(double), std::pair<double, double> ab, double step);
bool value_in_vect(double v, std::vector<double>&vect);

double prim(double (*f)(double), double x);

const double EPSILON = 1e-7;
const int ITERATION_LIMIT = 10;
const double MAX_STEP = 0.1;
const double VAL_DIFF_EPSILON = 1e-5;
const double DERIVATIVE_EPSILON = 1e-8;

extern int count_newton;
extern int count_secant;
extern int count_bisection;
extern int count_regula_falsi;

#endif