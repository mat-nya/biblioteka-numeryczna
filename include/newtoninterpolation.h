#pragma once
#include <vector>

double naturalna(int n, double x, std::vector <double>& an);
double hornera(int max, double x, std::vector <double>&an, int n = 0);
std::vector <double> policz_wspolczynniki(std::vector <double> x, std::vector <double> f);
double interpolacja_newtona(std::vector <double> a, std::vector <double> xWezly, double x);