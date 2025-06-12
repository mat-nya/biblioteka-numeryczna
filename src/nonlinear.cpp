#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <nonlinear.h>


// Pochodna numeryczna
double numerical_derivative(double (*func)(double), double x) {
    return (func(x + H) - func(x - H)) / (2 * H);
}

double bisection(double (*func)(double), double a, double b, int& iterations, std::vector<double>& approximations) {
    if (func(a) * func(b) > 0) {
        return NAN; // brak zmiany znaku
    }

    iterations = 0;
    approximations.clear();

    while (abs(b - a) > EPS && iterations < MAX_ITER) {
        double c = (a + b) / 2.0;
        approximations.push_back(c);

        if (abs(func(c)) < EPS) {
            iterations++;
            return c;
        }

        if (func(a) * func(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        iterations++;
    }

    return (a + b) / 2.0;
}

// Metoda Newtona
double newton(double (*func)(double), double (*derivative)(double), double x0, int& iterations, std::vector<double>& approximations) {
    iterations = 0;
    approximations.clear();
    double x = x0;

    while (iterations < MAX_ITER) {
        approximations.push_back(x);
        double fx = func(x);
        double dfx = derivative(x);

        if (abs(fx) < EPS) {
            return x;
        }

        if (abs(dfx) < EPS) {
            return NAN; // pochodna zbyt ma³a
        }

        double x_new = x - fx / dfx;

        if (abs(x_new - x) < EPS) {
            return x_new;
        }

        x = x_new;
        iterations++;
    }

    return x;
}

// Metoda Newtona z pochodn¹ numeryczn¹
double newton_numerical(double (*func)(double), double x0, int& iterations, std::vector<double>& approximations) {
    iterations = 0;
    approximations.clear();
    double x = x0;

    while (iterations < MAX_ITER) {
        approximations.push_back(x);
        double fx = func(x);
        double dfx = numerical_derivative(func, x);

        if (abs(fx) < EPS) {
            return x;
        }

        if (abs(dfx) < EPS) {
            return NAN;
        }

        double x_new = x - fx / dfx;

        if (abs(x_new - x) < EPS) {
            return x_new;
        }

        x = x_new;
        iterations++;
    }

    return x;
}

// Metoda siecznych
double secant(double (*func)(double), double x0, double x1, int& iterations, std::vector<double>& approximations) {
    iterations = 0;
    approximations.clear();

    while (iterations < MAX_ITER) {
        approximations.push_back(x1);
        double fx0 = func(x0);
        double fx1 = func(x1);

        if (abs(fx1) < EPS) {
            return x1;
        }

        if (abs(fx1 - fx0) < EPS) {
            return NAN;
        }

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

        if (abs(x2 - x1) < EPS) {
            return x2;
        }

        x0 = x1;
        x1 = x2;
        iterations++;
    }

    return x1;
}

// Znajdowanie przedzia³ów ze zmian¹ znaku
std::vector<std::pair<double, double>> find_sign_change_intervals(double (*func)(double), double start, double end, double step) {
    std::vector<std::pair<double, double>> intervals;

    for (double x = start; x < end; x += step) {
        double f_x = func(x);
        double f_x_next = func(x + step);

        if (f_x * f_x_next < 0) {
            intervals.push_back({ x, x + step });
        }
    }

    return intervals;
}
