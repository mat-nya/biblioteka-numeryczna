#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <functional>
#include <iostream>
#include <integration.h>


double zmiana_przedzialu(double a, double b, double x) {
	return 0.5 * (b - a) * x + 0.5 * (b + a);
}

double gauss_legendre(std::function <double(double)> f, double a, double b, int n) {
	std::vector<double> x, wagi; // do³o¿yæ so wykresów wczeœniejszych
	if (n == 2) {
		x = { -1.0 / sqrt(3.0), 1.0 / sqrt(3.0) };
		wagi = { 1.0, 1.0 };
	}
	else if (n == 3) {
		x = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
		wagi = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
	}
	else if (n == 4) {
		x = { -sqrt(3.0 / 7.0 + 2.0 / 7.0 * sqrt(6.0 / 5.0)), -sqrt(3.0 / 7.0 - 2.0 / 7.0 * sqrt(6.0 / 5.0)), sqrt(3.0 / 7.0 - 2.0 / 7.0 * sqrt(6.0 / 5.0)), sqrt(3.0 / 7.0 + 2.0 / 7.0 * sqrt(6.0 / 5.0)) };
		wagi = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };
	}
	else if (n == 5) {
		x = { -sqrt((5.0 + 2.0 * sqrt(10.0 / 7.0)) / 9.0), -sqrt((5.0 - 2.0 * sqrt(10.0 / 7.0)) / 9.0), 0.0, sqrt((5.0 - 2.0 * sqrt(10.0 / 7.0)) / 9.0), sqrt((5.0 + 2.0 * sqrt(10.0 / 7.0)) / 9.0) };
		wagi = { (322.0 - 13.0 * sqrt(70.0)) / 900.0, (322.0 + 13.0 * sqrt(70.0)) / 900.0, 128.0 / 225.0, (322.0 + 13.0 * sqrt(70.0)) / 900.0, (322.0 - 13.0 * sqrt(70.0)) / 900.0 };

	}
	else {
		std::cout << "Nieobslugiwana liczba wezlow: " << n << std::endl;
		return 0;
	}

	double suma = 0.0;
	for (int i = 0; i < n; ++i) {
		double xi = zmiana_przedzialu(a, b, x[i]);
		suma += wagi[i] * f(xi);
	}

	return 0.5 * (b - a) * suma;
}

double gauss_legendre_z_podzialem(std::function<double(double)> f, double a, double b, int n, int podzialy) {
	double suma = 0.0;
	double krok = (b - a) / podzialy;

	for (int i = 0; i < podzialy; ++i) {
		double a_i = a + i * krok;
		double b_i = a + (i + 1) * krok;
		suma += gauss_legendre(f, a_i, b_i, n);
	}

	return suma;
}