#include <approximation.h>
#include <cmath>
#include <functional>
#include <vector>
#include <iostream>


double funkcja(double x) {
    return exp(x) * cos(5 * x) - pow(x, 3);
}

double simpson(std::function<double(double)> func, double a, double b, int n) {
    if (n % 2 != 0) {
        std::cout << "Nieparzysta dokladnosc, nie mozna policzyc Simpsona" << std::endl;
        return 0;
    }

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i += 2)
        sum += 4 * func(a + i * h);

    for (int i = 2; i < n; i += 2)
        sum += 2 * func(a + i * h);

    return (h / 3) * sum;
}

void uklad_rownan(int stopien, double a, double b, int przedzialy, std::vector<std::vector<double>>& A, std::vector<double>& B) {
    A.resize(stopien + 1, std::vector<double>(stopien + 1, 0)); // zmieniamy wielkosci (bo na razie jest 0) i wypelniamy 0
    B.resize(stopien + 1, 0); // tutaj tak samo
    for (int j = 0; j <= stopien; j++) {
        std::function<double(double)> bj = [j](double x) { // uzupe³nianie B
            return funkcja(x) * pow(x, j);
            };
        B[j] = simpson(bj, a, b, przedzialy);
        for (int i = 0; i <= stopien; i++) {
            std::function <double(double)> aij = [i, j](double x) {
                return pow(x, i) * pow(x, j);
                };
            A[j][i] = simpson(aij, a, b, przedzialy);
        }
    }
}

