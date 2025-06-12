#pragma once
#include <vector>

void zamien_wiersze(std::vector<std::vector<double>>& A, std::vector<double>& b, int wiersz1, int wiersz2);
int znajdz_max_pivot(std::vector<std::vector<double>>& A, int row, int start_row);
bool eliminacja_gaussa(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x);
void sprawdz_rozwiazanie(std::vector<std::vector<double>>& A_pierwotne, const std::vector<double>& b_pierwotne, std::vector<double>& x);
void wypisz_macierz(std::vector <std::vector <double>> A, std::vector <double> b);