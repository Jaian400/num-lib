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
# define M_PI 3.14159265358979323846

/*
Założenia:

    1. W przedziale [ a , b ] {\displaystyle [a,b]} znajduje się dokładnie jeden pierwiastek funkcji f . {\displaystyle f.}
    2. Funkcja ma różne znaki na krańcach przedziału, tj. f ( a ) ⋅ f ( b ) < 0. {\displaystyle f(a)\cdot f(b)<0.}
    3. Pierwsza i druga pochodna funkcji mają stały znak w tym przedziale.
*/

// ---------------------METHODS-------------------------------------

// Solve nonlinear equation - Newton's method - not recommended
// f - function to solve
// f_prim - derivative of a function
// y0 - point near which the search will take place
double solve_nonlinear_newton(double (*f)(double), double(*f_prim)(double), double y0);
// Solve nonlinear equation - Newton's method - not recommended
// f - function to solve
// y0 - point near which the search will take place
double solve_nonlinear_newton(double (*f)(double), double y0);
// Solve nonlinear equation - secants method - not recommended
// f - function to solve
// y0 - point near which the search will take place
// y_p - previous point
double solve_nonlinear_secant(double (*f)(double), double y0, double y_p);
// Solve nonlinear equation - bisection method - returns only one point from interval
// f - function to solve
// a - start of interval
// b - end of interval
double solve_nonlinear_bisection(double (*f)(double), double a, double b);
// Solve nonlinear equation - regula falsi method - returns only one point from interval
// f - function to solve
// a - start of interval
// b - end of interval
double solve_nonlinear_regula_falsi(double (*f)(double), double a, double b);

// -----------------------MAIN-SCRIPT---------------------------------------

// Solve nonlinear equation - find all function roots in interval
// f - function to solve
// [a, b] - examined interval
std::vector<double> solve_nonlin_eq(double (*f)(double), std::pair<double, double> ab);
// Solve nonlinear equation - find roots of a function
// f - function to solve
// [a, b] - examined interval
// step - discretization interval size - the smallest interval that will be examined
std::vector<double> solve_nonlin_eq(double (*f)(double), std::pair<double, double> ab, double step);

// ------------------------HELPERS-------------------------------

// Returns true if vector contains value, restricted by precision of VAL_DIFF_EPSILON
// v - value
// vect - vector
bool value_in_vect(double v, std::vector<double>&vect);

double prim(double (*f)(double), double x);

// -----------------------CONSTS-----------------------------------

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