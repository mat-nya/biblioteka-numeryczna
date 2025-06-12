#include <differentialequation.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

double wzor(double T, double alfa, double beta) {
	return -alfa * (pow(T, 4) - beta);
}

std::vector<std::pair<double, double>> euler(double yi, double alfa, double beta, double czas, double przedzialy) {
	std::vector<std::pair<double, double>> wynik;
	double h = czas / przedzialy; // t_koncowy - t_poczatkowy (=0) / przedzialy
	double xi = 0;
	wynik.push_back(std::make_pair(xi, yi));
	for (int i = 1; i <= przedzialy; i++) {
		double xii = i * h;
		double yii = yi + h * wzor(yi, alfa, beta);
		wynik.push_back(std::make_pair(xii, yii));
		yi = yii;
	}
	return wynik;
}

std::vector<std::pair<double, double>> heun(double yi, double alfa, double beta, double czas, double przedzialy) {
	std::vector<std::pair<double, double>> wynik;
	double h = czas / przedzialy; // t_koncowy - t_poczatkowy (=0) / przedzialy
	double xi = 0;
	wynik.push_back(std::make_pair(xi, yi));
	for (int i = 1; i <= przedzialy; i++) {
		double xii = i * h;
		double yii = yi + h / 2 * (wzor(yi, alfa, beta) + wzor(yi + h * wzor(yi, alfa, beta), alfa, beta));
		wynik.push_back(std::make_pair(xii, yii));
		yi = yii;
	}
	return wynik;
}

std::vector<std::pair<double, double>> punkt_srodkowy(double yi, double alfa, double beta, double czas, double przedzialy) {
	std::vector<std::pair<double, double>> wynik;
	double h = czas / przedzialy; // t_koncowy - t_poczatkowy (=0) / przedzialy
	double xi = 0;
	wynik.push_back(std::make_pair(xi, yi));
	for (int i = 1; i <= przedzialy; i++) {
		double xii = i * h;
		double yii = yi + h * wzor(yi + (h / 2) * wzor(yi, alfa, beta), alfa, beta);
		wynik.push_back(std::make_pair(xii, yii));
		yi = yii;
	}
	return wynik;
}

std::vector<std::pair<double, double>> runge_kutta(double yi, double alfa, double beta, double czas, double przedzialy) {
	std::vector<std::pair<double, double>> wynik;
	double h = czas / przedzialy; // t_koncowy - t_poczatkowy (=0) / przedzialy
	double xi = 0;
	wynik.push_back(std::make_pair(xi, yi));
	for (int i = 1; i <= przedzialy; i++) {
		double xii = i * h;
		double k1 = h * wzor(yi, alfa, beta);
		double k2 = h * wzor(yi + k1 / 2, alfa, beta);
		double k3 = h * wzor(yi + k2 / 2, alfa, beta);
		double k4 = h * wzor(yi + k3, alfa, beta);
		double yii = yi + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		wynik.push_back(std::make_pair(xii, yii));
		yi = yii;
	}
	return wynik;
}