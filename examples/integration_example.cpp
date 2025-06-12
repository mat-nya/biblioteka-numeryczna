#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>
#include <functional>
#include <iomanip>
#include <integration.h>

using namespace std;

//funkcje z zadania
double f1(double x) {
	return pow(x, 2) * pow(sin(x), 3);
}

double f2(double x) {
	return pow(M_E, pow(x, 2)) * (1 - x);
}

double f3(double x) {
	return (28 - 20 * x - 18 * pow(x, 2) + 13 * pow(x, 3) - 9 * pow(x, 4) + 8 * pow(x, 5) + 16 * pow(x, 6));
}

int main() {
	cout << fixed << setprecision(10);
	int k[4] = {6, 10, 100, 1000};

	//bez przedzia³ów

	/*double dokladne_f1 = -10.1010101105;
	cout << "Calka z f1(x):\n";
	for (int n = 2; n <= 5; ++n) {
		double wynik = gauss_legendre(f1, 1, 4.764798248, n);
		cout << n << " wezly: " << wynik << "\t\tblad: " << abs(wynik - dokladne_f1) << endl;
	}

	double dokladne_f2 = -9909.4484656064;

	cout << "\nCalka z f2(x):\n";
	for (int n = 2; n <= 5; ++n) {
		double wynik = gauss_legendre(f2, 2, 3.20870913294, n);
		cout << n << " wezly: " << wynik << "\tblad: " << abs(wynik - dokladne_f2) << endl;
	}*/

	//z przedzia³ami

	/*for (int i = 0; i < 4; i++) {
		cout << "------- " << k[i] << " przedzialow -------\n";
		double dokladne_f1 = -10.1010101105;
		cout << "Calka z f1(x):\n";
		for (int n = 2; n <= 5; ++n) {
			double wynik = gauss_legendre_z_podzialem(f1, 1, 4.764798248, n, k[i]);
			cout << n << " wezly: " << wynik << "\t\tblad: " << abs(wynik - dokladne_f1) << endl;
		}

		double dokladne_f2 = -9909.4484656064;

		cout << "\nCalka z f2(x):\n";
		for (int n = 2; n <= 5; ++n) {
			double wynik = gauss_legendre_z_podzialem(f2, 2, 3.20870913294, n, k[i]);
			cout << n << " wezly: " << wynik << "\tblad: " << abs(wynik - dokladne_f2) << endl;
		}
	}*/

	//funkcja z poprzednich zajêæ

	for (int i = 0; i < 4; i++) {
		cout << "------- " << k[i] << " przedzialow -------\n";
		double dokladne_f3 = 29217.6785714286;
		cout << "Calka z f3(x):\n";
		for (int n = 2; n <= 5; ++n) {
			double wynik = gauss_legendre_z_podzialem(f3, -4, 1, n, k[i]);
			cout << n << " wezly: " << wynik << "\t\tblad: " << abs(wynik - dokladne_f3) << endl;
		}
	}
}