#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <differentialequation.h>
using namespace std;

double dokladna_funkcja(double x) {
	return 1480000 / pow(244140625 + 77803008 * x, 1.0 / 3.0);
}

int main() {
	double T = 2368; // Kelwiny
	double alfa = 8e-12;
	double beta = 0;
	double czas = 2368; // sekundy
	double N[10] = { 500, 750, 1000 }; // iloœæ przedzia³ów h od 500 zaczyna rosn¹æ, przy 700 maleæ
	ofstream e_bledy("e_bledy.csv");
	e_bledy << "krok,MSE\n";
	for (int i = 0; i < 3; i++) {
		vector<pair<double, double>> wynik = euler(T, alfa, beta, czas, N[i]);
		ofstream e_plik("e_wynik" + to_string(i) + ".csv");
		e_plik << "czas,e_temperatura,temperatura" << endl;
		double blad_kwadratowy = 0;
		double h = czas / N[i];
		for (int n = 0; n <= N[i]; n++) {
			double t = wynik[n].first;
			double Te = wynik[n].second;
			double Td = dokladna_funkcja(t);
			blad_kwadratowy += pow(Te - Td, 2);
			e_plik << t << "," << Te << "," << Td << endl;
		}
		e_bledy << h << "," << blad_kwadratowy / (N[i] + 1) << endl;
		e_plik.close();
	}
	e_bledy.close();

	ofstream h_bledy("h_bledy.csv");
	h_bledy << "krok,MSE\n";
	for (int i = 0; i <= 3; i++) {
		vector<pair<double, double>> wynik = heun(T, alfa, beta, czas, N[i]);
		ofstream h_plik("h_wynik" + to_string(N[i]) + ".csv");
		h_plik << "czas,e_temperatura,temperatura" << endl;
		double blad_kwadratowy = 0;
		double h = czas / N[i];
		for (int n = 0; n <= N[i]; n++) {
			double t = wynik[n].first;
			double Te = wynik[n].second;
			double Td = dokladna_funkcja(t);
			blad_kwadratowy += pow(Te - Td, 2);
			h_plik << t << "," << Te << "," << Td << endl;
		}
		h_bledy << h << "," << blad_kwadratowy / (N[i] + 1) << endl;
		h_plik.close();
	}
	h_bledy.close();

	ofstream p_s_bledy("pœ_bledy.csv");
	p_s_bledy << "krok,MSE\n";
	for (int i = 0; i < 3; i++) {
		vector<pair<double, double>> wynik = punkt_srodkowy(T, alfa, beta, czas, N[i]);
		ofstream p_s_plik("pœ_wynik" + to_string(i) + ".csv");
		p_s_plik << "czas,e_temperatura,temperatura" << endl;
		double blad_kwadratowy = 0;
		double h = czas / N[i];
		for (int n = 0; n <= N[i]; n++) {
			double t = wynik[n].first;
			double Te = wynik[n].second;
			double Td = dokladna_funkcja(t);
			blad_kwadratowy += pow(Te - Td, 2);
			p_s_plik << t << "," << Te << "," << Td << endl;
		}
		p_s_bledy << h << "," << blad_kwadratowy / (N[i] + 1) << endl;
		p_s_plik.close();
	}
	p_s_bledy.close();

	ofstream rk_bledy("RK_bledy.csv");
	rk_bledy << "krok,MSE\n";
	for (int i = 0; i < 3; i++) {
		vector<pair<double, double>> wynik = runge_kutta(T, alfa, beta, czas, N[i]);
		ofstream rk_plik("RK_wynik" + to_string(i) + ".csv");
		rk_plik << "czas,e_temperatura,temperatura" << endl;
		double blad_kwadratowy = 0;
		double h = czas / N[i];
		for (int n = 0; n <= N[i]; n++) {
			double t = wynik[n].first;
			double Te = wynik[n].second;
			double Td = dokladna_funkcja(t);
			blad_kwadratowy += pow(Te - Td, 2);
			rk_plik << t << "," << Te << "," << Td << endl;
		}
		rk_bledy << h << "," << blad_kwadratowy / (N[i] + 1) << endl;
		rk_plik.close();
	}
	rk_bledy.close();
}