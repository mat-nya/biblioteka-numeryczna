#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <gausselimination.h>
using namespace std;

void czytaj_plik_gauss_A(vector <double>& b, vector <vector <double>>& A, string filename) {
	fstream dane;
	dane.open(filename);
	if (!dane.good()) {
		cout << "brak pliku";
		return;
	}

	string line;
	string temp;

	// zapisywanie N i b
	int N;
	getline(dane, line); // śmieci
	getline(dane, line); // N
	N = stoi(line.erase(0, 4));
	getline(dane, line); // śmieci
	getline(dane, line); // b
	istringstream issb(line);
	while (issb >> temp) {
		b.push_back(stod(temp));
	}

	// zapisywanie A
	getline(dane, line); // śmieci
	A.resize(N, vector <double>(N));
	for (int n = 0; n < N; n++) {
		getline(dane, line); // A n-ty wiersz
		istringstream issa(line);
		for (int m = 0; m < N; m++) {
			issa >> temp;
			A[n][m] = stod(temp);
		}
	}
	dane.close(); // koniec wczytywania z pliku
}


int main() {
	vector<double> b;
	vector<vector <double>> A;
	czytaj_plik_gauss_A(b, A, "../../../data/gauss_elimination_gr1IO_A.txt");
	vector<double> b_original = b; // zapisanie kopii
	vector<vector<double>> A_original = A;
	cout << "Input: " << endl;
	wypisz_macierz(A, b); // wypisanie wszysttkiego

	vector<double> x;
	bool rozwiazano = eliminacja_gaussa(A, b, x);

	if (rozwiazano) {
		cout << "Rozwiazanie ukladu rownan:" << endl;
		for (int i = 0; i < x.size(); i++) {
			cout << "x[" << i + 1 << "] = " << x[i] << endl;
		}

		sprawdz_rozwiazanie(A_original, b_original, x);
	}
	else {
		cout << "Nie udalo sie rozwiazac ukladu rownan." << endl;
	}
	
	vector<double> bb;
	vector<vector <double>> Ab;
	czytaj_plik_gauss_A(bb, Ab, "../../../data/gauss_elimination_gr1IO_B.txt");
	vector<double> bb_original = bb; // zapisanie kopii
	vector<vector<double>> Ab_original = Ab;
	cout << "Input: " << endl;
	wypisz_macierz(Ab, bb); // wypisanie wszysttkiego

	vector<double> xb;
	bool rozwiazanob = eliminacja_gaussa(Ab, bb, xb);

	if (rozwiazanob) {
		cout << "Rozwiazanie ukladu rownan:" << endl;
		for (int i = 0; i < xb.size(); i++) {
			cout << "x[" << i + 1 << "] = " << xb[i] << endl;
		}

		sprawdz_rozwiazanie(Ab_original, bb_original, xb);
	}
	else {
		cout << "Nie udalo sie rozwiazac ukladu rownan." << endl;
	}


	vector<double> bc;
	vector<vector <double>> Ac;
	czytaj_plik_gauss_A(bc, Ac, "../../../data/gauss_elimination_gr1IO_C.txt");
	vector<double> bc_original = bc; // zapisanie kopii
	vector<vector<double>> Ac_original = Ac;
	cout << "Input: " << endl;
	wypisz_macierz(Ac, bc); // wypisanie wszysttkiego

	vector<double> xc;
	bool rozwiazanoc = eliminacja_gaussa(Ac, bc, xc);

	if (rozwiazanoc) {
		cout << "Rozwiazanie ukladu rownan:" << endl;
		for (int i = 0; i < xc.size(); i++) {
			cout << "x[" << i + 1 << "] = " << xc[i] << endl;
		}

		sprawdz_rozwiazanie(Ac_original, bc_original, xc);
	}
	else {
		cout << "Nie udalo sie rozwiazac ukladu rownan." << endl;
	}
	
}