#pragma once
#include <functional>
#include <vector>

double funkcja(double x);
double simpson(std::function<double(double)> func, double a, double b, int n);
void uklad_rownan(int stopien, double a, double b, int przedzialy, std::vector<std::vector<double>>& A, std::vector<double>& B);
