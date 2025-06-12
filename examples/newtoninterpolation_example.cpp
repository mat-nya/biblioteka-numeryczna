#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <newtoninterpolation.h>
using namespace std;
using namespace std::chrono;

void czytaj_plik_wielomian(vector <double>& an, vector <double>& xi) {
	fstream dane;
	dane.open("../../../data/interpolacja_H_gr_01.txt");
	if (!dane.good()) {
		cout << "brak pliku";
		return;
	}

	string line;
	string temp;

	// zapisywanie an
	getline(dane, line);
	getline(dane, line);
	istringstream issa(line);
	while (issa >> temp) {
		an.push_back(stod(temp.erase(0, 3)));
	}

	// zapisywanie xi
	getline(dane, line);
	istringstream issy(line);
	issy >> temp;
	while (issy >> temp) {
		xi.push_back(stod(temp));
	}

	dane.close(); // koniec wczytywania z pliku
}

void czytaj_plik_interpolacja(vector <double>& xi, vector <double>& fi) {
	fstream dane;
	dane.open("../../../data/interpolacja_N_gr_01.txt");
	if (!dane.good()) {
		cout << "brak pliku";
		return;
	}

	string line;
	string temp;

	// zapisywanie xi
	getline(dane, line);
	getline(dane, line);
	istringstream issx(line);
	issx >> temp;
	while (issx >> temp) {
		xi.push_back(stod(temp));
	}

	// zapisywanie f(xi)
	getline(dane, line);
	istringstream issy(line);
	issy >> temp;
	while (issy >> temp) {
		fi.push_back(stod(temp));
	}

	dane.close(); // koniec wczytywania z pliku
}


int main() {
	vector <double> an;
	vector <double> xi;
	czytaj_plik_wielomian(an, xi);
	
	/*cout << "an \t xi\n";
	for (int i = 0; an.size() > i; i++) {
		cout << fixed << setprecision(4) << an[i] << "\t" << xi[i] << endl;
	}
	*/

	ofstream wyniki("wyniki.csv");
	wyniki << "xi,n,Czas naturalny,Wynik naturalny,Czas Hornera,Wynik Hornera,Ró¿nica wyników\n";
	for (int n = 3; n < 8; n += 2) {
		double* wynik_n = new double[xi.size()];
		auto start = high_resolution_clock::now(); // rozpoczêcie liczenia czasu
		for (int i = 0; i < xi.size(); i++) {
			wynik_n[i] = naturalna(n, xi[i], an);
		}
		auto stop = high_resolution_clock::now();
		auto czas_n = duration_cast<microseconds>(stop - start);
		double* wynik_h = new double[xi.size()];
		start = high_resolution_clock::now(); // rozpoczêcie liczenia czasu
		for (int i = 0; i < xi.size(); i++) {
			wynik_h[i] = hornera(n, xi[i], an);
		}
		stop = high_resolution_clock::now();
		auto czas_h = duration_cast<microseconds>(stop - start);
		cout << "Ilosc wspolczynnikow: " << n << endl;
		cout << "Czas wykonywania dla postaci naturalnej: " << czas_n.count() << " microseconds" << endl;
		cout << "Czas wykonywania dla postaci Hornera: " << czas_h.count() << " microseconds" << endl;
		for (int k = 0; k < xi.size(); k++) {
			wyniki << k << "," << n << "," << czas_n.count() << "," << wynik_n[k] << "," << czas_h.count() << "," << wynik_h[k] << "," << fabs(wynik_n[k] - wynik_h[k]) << "\n";
		}
	}
	wyniki.close();

	cout << "\n\n-----Druga czesc zadania-----\n\n";

	vector <double> x;
	vector <double> f;
	czytaj_plik_interpolacja(x, f);
	vector <double> xiWezlowy, fiWezlowy;
	for (int i = 0; i < x.size(); i++) {
		if (i % 5 == 0) {
			xiWezlowy.push_back(x[i]);
			fiWezlowy.push_back(f[i]);
		}
	}
	vector <double> a = policz_wspolczynniki(xiWezlowy, fiWezlowy);

	ofstream wynikiInterpolacji("interpolacjaNewtona.csv");
	wynikiInterpolacji << "x dane,f dane,f policzone\n";
	for (int i = 0; i < x.size(); i++) {
		wynikiInterpolacji << x[i] << "," << f[i] << "," << interpolacja_newtona(a, xiWezlowy, x[i]) << endl;
	}
	wynikiInterpolacji.close();

	ofstream wezly("wezly.csv");
	wezly << "x wêze³,y wêze³\n";
	for (int i = 0; i < xiWezlowy.size(); i++) {
		wezly << xiWezlowy[i] << "," << fiWezlowy[i] << endl;
	}
	double input;
	cout << "Podaj x: ";
	cin >> input;
	cout << fixed << setprecision(2) << "F(" << input << ") = " << interpolacja_newtona(a, xiWezlowy, input);
}