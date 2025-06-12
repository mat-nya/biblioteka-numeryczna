#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <iomanip>
#include <fstream>
#include <gausselimination.h>
#include <approximation.h>

using namespace std;


void wypisz_wielomian(const vector<double>& wsp) {
	cout << "Wielomian aproksymujacy:" << endl;
	for (int i = 0; i < wsp.size(); ++i) {
		cout << fixed << setprecision(6) << wsp[i] << " * x^" << i;
		if (i != wsp.size() - 1) cout << " + ";
	}
	cout << endl;
}

double blad_sredniokwadratowy(function<double(double)> f, const vector<double>& wsp, double a, double b, int n) {
	auto roznica_kwadrat = [&](double x) {
		double Px = 0;
		for (int i = 0; i < wsp.size(); ++i) {
			Px += wsp[i] * pow(x, i);
		}
		return pow(f(x) - Px, 2);
		};
	return simpson(roznica_kwadrat, a, b, n) / (b - a);
}

void zbadaj_blad_dla_roznych_stopni(double a, double b, int przedzialy, int max_stopien) {
	ofstream plik("bledy_dla_stopni.csv");
	plik << "stopien,blad\n";

	for (int stopien = 1; stopien <= max_stopien; ++stopien) {
		vector<vector<double>> A;
		vector<double> B, wsp;

		uklad_rownan(stopien, a, b, przedzialy, A, B);
		if (eliminacja_gaussa(A, B, wsp)) {
			double blad = blad_sredniokwadratowy(funkcja, wsp, a, b, przedzialy);
			plik << stopien << "," << blad << "\n";
		}
	}
	plik.close();
}

void zapisz_blad_do_pliku(const vector<double>& wsp, double a, double b, int liczba_punktow) {
	ofstream plik("blad.csv");
	plik << "x,blad\n";

	for (int i = 0; i <= liczba_punktow; ++i) {
		double x = a + i * (b - a) / liczba_punktow;
		double fx = funkcja(x);
		double Px = 0;
		for (int j = 0; j < wsp.size(); ++j)
			Px += wsp[j] * pow(x, j);
		double blad = fabs(fx - Px);
		plik << x << "," << blad << "\n";
	}
	plik.close();
}

void zapisz_wykres(const vector<double>& x, const vector<double>& fx, const vector<double>& px) {
	ofstream plik("wykres.csv");
	plik << "x,f(x),P(x),blad_abs\n";
	for (int i = 0; i < x.size(); ++i) {
		double blad = fabs(fx[i] - px[i]);
		plik << x[i] << "," << fx[i] << "," << px[i] << "," << blad << "\n";
	}
	plik.close();
}

int main() {
	double a = 0.0, b = 1.5;
	int stopien = 6;
	int przedzialy = 100;

	vector<vector<double>> A;
	vector<double> B, wspolczynniki;

	uklad_rownan(stopien, a, b, przedzialy, A, B);

	if (eliminacja_gaussa(A, B, wspolczynniki)) {
		wypisz_wielomian(wspolczynniki);
	}

	vector<double> x_vals, f_vals, p_vals;

	int N = 100; // liczba punktów na wykresie

	double blad = blad_sredniokwadratowy(funkcja, wspolczynniki, a, b, przedzialy);
	cout << "Blad sredniokwadratowy aproksymacji: " << blad << endl;

	for (int i = 0; i <= N; ++i) {
		double x = a + i * (b - a) / N;
		double fx = funkcja(x);

		// wartoœæ aproksymacji P(x)
		double px = 0;
		for (int j = 0; j < wspolczynniki.size(); ++j) {
			px += wspolczynniki[j] * pow(x, j);
		}

		x_vals.push_back(x);
		f_vals.push_back(fx);
		p_vals.push_back(px);
	}

	zapisz_wykres(x_vals, f_vals, p_vals);
	zbadaj_blad_dla_roznych_stopni(a, b, przedzialy, 10);
	zapisz_blad_do_pliku(wspolczynniki, a, b, N);
}