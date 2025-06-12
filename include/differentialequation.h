#pragma once
#include <vector>

double wzor(double T, double alfa, double beta);
std::vector<std::pair<double, double>> euler(double yi, double alfa, double beta, double czas, double przedzialy);
std::vector<std::pair<double, double>> heun(double yi, double alfa, double beta, double czas, double przedzialy);
std::vector<std::pair<double, double>> punkt_srodkowy(double yi, double alfa, double beta, double czas, double przedzialy);
std::vector<std::pair<double, double>> runge_kutta(double yi, double alfa, double beta, double czas, double przedzialy);
