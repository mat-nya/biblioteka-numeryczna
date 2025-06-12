#include <iostream>
#include <vector>
#include <iomanip>
#include <lumethod.h>

std::vector<double> rozwiaz_Lz(const std::vector<std::vector<double>>& L, const std::vector<double>& b) { // rozwi¹zywanie podstawianiem w przód
	int N = L.size();
	std::vector<double> z(N);
	for (int i = 0; i < N; i++) {
		double suma = 0;
		for (int j = 0; j < i; j++) {
			suma += L[i][j] * z[j];
		}
		z[i] = b[i] - suma;
	}
	return z;
}

std::vector<double> rozwiaz_Ux(const std::vector<std::vector<double>>& U, const std::vector<double>& z) { // podstawianie wstecz
	int N = U.size();
	std::vector<double> x(N);
	for (int i = N - 1; i >= 0; i--) {
		double suma = 0;
		for (int j = i + 1; j < N; j++) {
			suma += U[i][j] * x[j];
		}
		x[i] = (z[i] - suma) / U[i][i];
	}
	return x;
}

void tworzenie_lu(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
	int N = A.size();
	L.resize(N, std::vector<double>(N, 0));
	U.resize(N, std::vector<double>(N, 0)); // zmieniamy rozmiary (da³oby siê te¿ utworzyæ w mainie takie rozmiary

	for (int k = 0; k < N; k++) { // powtarzamy dla ka¿dego wiersza
		for (int j = k; j < N; j++) { // dla ka¿dej kolumny U
			double suma = 0;
			for (int s = 0; s <= k - 1; s++) {
				suma += L[k][s] * U[s][j];
			}
			U[k][j] = A[k][j] - suma;
		}
		for (int i = k; i < N; i++) { // dla ka¿dej kolumny L
			if (i == k) {
				L[k][k] = 1; // na przek¹tnych 1
			}
			else {
				double suma = 0;
				for (int s = 0; s <= k - 1; s++) {
					suma += L[i][s] * U[s][k];
				}
				if (U[k][k] == 0) {
					std::cout << "Dzielenie przez 0" << std::endl; // gdy macierzy siê tym sposobem nie da rozwi¹zaæ
					return;
				}

				L[i][k] = (A[i][k] - suma) / U[k][k];
			}
		}
		std::cout << "\nIteracja k = " << k + 1 << std::endl;

		std::cout << "Macierz L:\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << std::setw(10) << L[i][j];
			}
			std::cout << std::endl;
		}

		std::cout << "Macierz U:\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << std::setw(10) << U[i][j];
			}
			std::cout << std::endl;
		}
	}

}

void sprawdz_rozwiazanie(std::vector<std::vector<double>>& A_pierwotne, const std::vector<double>& b_pierwotne, std::vector<double>& x) {
	int N = A_pierwotne.size();
	double max_blad = 0;

	std::cout << "Sprawdzenie poprawnosci rozwiazania:" << std::endl;
	for (int i = 0; i < N; i++) {
		double suma = 0;
		for (int j = 0; j < N; j++) {
			suma += A_pierwotne[i][j] * x[j];
		}

		double blad = fabs(suma - b_pierwotne[i]);
		std::cout << "Rownanie " << i + 1 << ": ";
		std::cout << suma << " = " << b_pierwotne[i] << " (blad: " << blad << ")" << std::endl;

		if (blad > max_blad) {
			max_blad = blad;
		}
	}

	std::cout << "Maksymalny blad: " << max_blad << std::endl;
	if (max_blad < 1e-8) {
		std::cout << "Rozwiazanie jest poprawne." << std::endl;
	}
	else {
		std::cout << "Uwaga: Rozwiazanie moze nie byc dokladne." << std::endl;
	}
}
