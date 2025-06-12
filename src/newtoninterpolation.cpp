#include <vector>
#include <newtoninterpolation.h>

double naturalna(int n, double x, std::vector <double>& an) {
	double wynik = 0;
	for (int j = 0; j < n; j++) {
		wynik += an[j] * pow(x, j);
	}
	return wynik;
}

double hornera(int max, double x, std::vector <double>& an, int n) {
	if (n >= max) {
		return 0;
	}
	double wynik = 0;
	wynik = an[n] + x * hornera(max, x, an, n + 1);
	return wynik;
}

std::vector <double> policz_wspolczynniki(std::vector <double> x, std::vector <double> f) {
	int n = x.size();
	std::vector <std::vector<double>> tabela(n, std::vector <double>(n)); // tworzymy macierz, wielkoœæ n, n
	for (int i = 0; i < n; i++) { // pierwsza kolumna to f
		tabela[i][0] = f[i];
	}

	for (int j = 1; j < n; j++) { // wype³nienie tabeli
		for (int i = 0; i < n - j; i++) { // j = 1 bo 0 to f
			tabela[i][j] = (tabela[i + 1][j - 1] - tabela[i][j - 1]) / (x[i + j] - x[i]);
		}
	}

	std::vector <double> a(n); // wielkoœæ n
	for (int i = 0; i < n; i++) {
		a[i] = tabela[0][i]; // wszystkie wspó³czynniki wyl¹dowa³y w pierwszym wierszu (w insrukcji na przek¹tnej)
	}
	return a;
}

double interpolacja_newtona(std::vector <double> a, std::vector <double> xWezly, double x) {
	double wynik = a[0];
	double iloczyn;
	for (int i = 1; i < xWezly.size(); i++) {
		iloczyn = 1;
		for (int j = 0; j < i; j++) {
			iloczyn *= x - xWezly[j];
		}
		wynik += a[i] * iloczyn;
	}
	return wynik;
}
