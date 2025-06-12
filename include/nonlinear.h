#pragma once
#include <vector>
const double EPS = 1e-10;
const int MAX_ITER = 1000;
const double H = 1e-8;


// Pochodna numeryczna
double numerical_derivative(double (*func)(double), double x);
double bisection(double (*func)(double), double a, double b, int& iterations, std::vector<double>& approximations);
double newton(double (*func)(double), double (*derivative)(double), double x0, int& iterations, std::vector<double>& approximations);
double newton_numerical(double (*func)(double), double x0, int& iterations, std::vector<double>& approximations);
double secant(double (*func)(double), double x0, double x1, int& iterations, std::vector<double>& approximations);
std::vector<std::pair<double, double>> find_sign_change_intervals(double (*func)(double), double start, double end, double step);
