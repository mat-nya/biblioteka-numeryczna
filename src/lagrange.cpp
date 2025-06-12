#include <lagrange.h>
#include <vector>

double lagrange(std::vector<double>& xiWezlowy, std::vector<double>& fiWezlowy, double x) {
    double wynik = 0;
    double wielomian = 1; // li
    for (int i = 0; i < xiWezlowy.size(); i++) {
        wielomian = 1;
        for (int j = 0; j < xiWezlowy.size(); j++) {
            if (i != j) {
                wielomian *= ((x - xiWezlowy[j]) / (xiWezlowy[i] - xiWezlowy[j]));
            }
        }
        wynik += (fiWezlowy[i] * wielomian);
    }
    return wynik;
}