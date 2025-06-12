#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <gausselimination.h>
#include <lumethod.h>
using namespace std;

void czytaj_plik(vector <double>& b, vector <vector <double>>& A, string filename) {
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
	getline(dane, line); // œmieci
	getline(dane, line); // N
	N = stoi(line.erase(0, 4));
	getline(dane, line); // œmieci
	getline(dane, line); // b
	istringstream issb(line);
	while (issb >> temp) {
		b.push_back(stod(temp));
	}

	// zapisywanie A
	getline(dane, line); // œmieci
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

void wypisz_macierz(vector <vector <double>> A, vector <double> b) {
	cout << "bi:\t";
	for (int i = 0; b.size() > i; i++) {
		cout << b[i] << "\t";
	}
	cout << "\n\nA:\n";
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			cout << setw(10) << A[i][j];
		}
		cout << endl;
	}
}


int main() {
	vector<double> b;
	vector<vector <double>> A;
	czytaj_plik(b, A, "../../../data/gauss_elimination_gr1IO_A.txt");
	vector<double> b_original = b; // zapisanie kopii
	vector<vector<double>> A_original = A;
	cout << "Input: " << endl;
	wypisz_macierz(A, b); // wypisanie wszysttkiego


	vector<vector<double>> L;
	vector<vector<double>> U;
	tworzenie_lu(A, L, U);

	cout << "\nMacierz L:\n";
	wypisz_macierz(L, vector<double>());
	cout << "\nMacierz U:\n";
	wypisz_macierz(U, vector<double>());

	vector<double> z = rozwiaz_Lz(L, b);
	vector<double> x = rozwiaz_Ux(U, z);

	cout << "\nWektor z (Lz = b):\n";
	for (int i = 0; i < z.size(); i++) {
		cout << "z[" << i + 1 << "] = " << z[i] << endl;
	}

	cout << "\nRozwiazanie x (Ux = z):\n";
	for (int i = 0; i < x.size(); i++) {
		cout << "x[" << i + 1 << "] = " << x[i] << endl;
	}

	sprawdz_rozwiazanie(A_original, b_original, x);
}