#include <gausselimination.h>
#include <iostream>
#include <string>
#include <vector>

void zamien_wiersze(std::vector<std::vector<double>>& A, std::vector<double>& b, int wiersz1, int wiersz2) {
	if (wiersz1 == wiersz2) return;

	// zamiana w A
	std::vector<double> temp_wiersz = A[wiersz1];
	A[wiersz1] = A[wiersz2];
	A[wiersz2] = temp_wiersz;

	// zamiana w b
	double temp_b = b[wiersz1];
	b[wiersz1] = b[wiersz2];
	b[wiersz2] = temp_b;
}

int znajdz_max_pivot(std::vector<std::vector<double>>& A, int row, int start_row) {
	int max_row = start_row;
	double max_val = fabs(A[start_row][row]); // wartoœæ bezwzglêdna dla liczby najdalej od 0

	for (int i = start_row + 1; i < A.size(); i++) {
		if (fabs(A[i][row]) > max_val) {
			max_val = fabs(A[i][row]);
			max_row = i;
		}
	}

	return max_row;
}

bool eliminacja_gaussa(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x) {
	int N = A.size();
	x.resize(N, 0); // rozmiar N, wype³nia zerami

	// tworzenie macierzy trójk¹ten, eliminacja
	for (int k = 0; k < N - 1; k++) { // N-1 bo ostatniego wiersza nie eliminujemy
		std::cout << "Krok " << k + 1 << " eliminacji:" <<  std::endl;

		int max_row = znajdz_max_pivot(A, k, k); // czêœciowy pivoting czyli szuka wiersza z najwiêkszym elementem w kolumnie k (aktualnej), zaczynamy od k bo jest na przek¹tnej

		if (max_row != k) { // zamiana wierszy
			zamien_wiersze(A, b, k, max_row);
			std::cout << "Zamieniono miejscami wiersze " << k << " i " << max_row <<  std::endl;
		}

		if (fabs(A[k][k]) < 1e-10) { // sprawdzenie czy wiersz jest liniowo zale¿ny (pivot bliski zeru)
			std::cout << "Ostrzezenie: Wiersz " << k << " jest liniowo zalezny od poprzednich." <<  std::endl; // sprawdzamy dalej czy uk³ad ma rozwi¹zania
		}

		// eliminacja elementów poni¿ej pivota
		for (int i = k + 1; i < N; i++) {
			double wspolczynnik = A[i][k] / A[k][k];

			for (int j = k; j < N; j++) {
				A[i][j] -= wspolczynnik * A[k][j]; // [i][k] ma byæ 0
			}
			b[i] -= wspolczynnik * b[k];
		}
		wypisz_macierz(A, b);
	}

	// czy ostatni wiersz nie jest sprzeczny (0 = niezerowa wartoœæ)
	if (fabs(A[N - 1][N - 1]) < 1e-10 && fabs(b[N - 1]) > 1e-10) {
		std::cout << "Uklad rownan jest sprzeczny." <<  std::endl;
		return false; // brak rozwi¹zania
	}

	// podstawianie wstecz, czyli liczymy x
	std::cout << "Podstawianie wstecz:" <<  std::endl;
	for (int i = N - 1; i >= 0; i--) {
		double suma = 0;
		for (int j = i + 1; j < N; j++) {
			suma += A[i][j] * x[j];
		}

		// czy nie dzielimy przez zero?
		if (fabs(A[i][i]) < 1e-10) {
			if (fabs(b[i] - suma) < 1e-10) {
				// nieskoñczenie wiele rozwi¹zañ, przyjmujemy x[i] = 0
				x[i] = 0;
				std::cout << "Ostrzezenie: Rownanie " << i << " ma nieskonczenie wiele rozwiazan." <<  std::endl;
			}
			else {
				std::cout << "Uklad rownan jest sprzeczny." <<  std::endl;
				return false; // nie da siê rozwi¹zaæ
			}
		}
		else {
			x[i] = (b[i] - suma) / A[i][i];
		}
	}

	return true; // znaleziono rozwiazanie
}

void sprawdz_rozwiazanie(std::vector<std::vector<double>>& A_pierwotne, const std::vector<double>& b_pierwotne, std::vector<double>& x) {
	int N = A_pierwotne.size();
	double max_blad = 0;

	std::cout << "Sprawdzenie poprawnosci rozwiazania:" <<  std::endl;
	for (int i = 0; i < N; i++) {
		double suma = 0;
		for (int j = 0; j < N; j++) {
			suma += A_pierwotne[i][j] * x[j];
		}

		double blad = fabs(suma - b_pierwotne[i]);
		std::cout << "Rownanie " << i + 1 << ": ";
		std::cout << suma << " = " << b_pierwotne[i] << " (blad: " << blad << ")" <<  std::endl;

		if (blad > max_blad) {
			max_blad = blad;
		}
	}

	std::cout << "Maksymalny blad: " << max_blad <<  std::endl;
	if (max_blad < 1e-8) {
		std::cout << "Rozwiazanie jest poprawne." <<  std::endl;
	}
	else {
		std::cout << "Uwaga: Rozwiazanie moze nie byc dokladne." <<  std::endl;
	}
}

void wypisz_macierz(std::vector <std::vector <double>> A, std::vector <double> b) {
	std::cout << "bi:\t";
	for (int i = 0; b.size() > i; i++) {
		std::cout << b[i] << "\t";
	}
	std::cout << "\n\nA:\n";
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			std::cout << A[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

