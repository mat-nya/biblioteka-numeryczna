#pragma once
#include <iostream>
#include <vector>

std::vector<double> rozwiaz_Lz(const std::vector<std::vector<double>>& L, const std::vector<double>& b);
std::vector<double> rozwiaz_Ux(const std::vector<std::vector<double>>& U, const std::vector<double>& z);
void tworzenie_lu(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U);
void sprawdz_rozwiazanie(std::vector<std::vector<double>>& A_pierwotne, const std::vector<double>& b_pierwotne, std::vector<double>& x);
