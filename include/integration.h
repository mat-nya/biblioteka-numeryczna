#pragma once
#include <vector>
#include <functional>

double zmiana_przedzialu(double a, double b, double x);
double gauss_legendre(std::function <double(double)> f, double a, double b, int n);
double gauss_legendre_z_podzialem(std::function<double(double)> f, double a, double b, int n, int podzialy);