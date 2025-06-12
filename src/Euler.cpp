#include "Euler.h"
#include <cmath>

#define alpha 7.0e-12
#define betha 0.0
#define TO 9617.0

// przedzia³y ró¿niczkowania
double a = 0.0;
double b = 9617.0;

// równanie zmiany temperatury
double eq(double T){
    return -alpha * (pow(T,4) - betha);
}

// metoda Eulera
std::vector<std::pair<double, double>> Euler(double N, double step){
    std::vector<std::pair<double, double>> solutions;
    double t = a;
    double Tprev = TO;
    double T;
    solutions.push_back(std::make_pair(t, TO));
    for (int i = 1; i <= N; i++){
        t = a + i * step;
        T = Tprev + step * eq(Tprev);
        solutions.push_back(std::make_pair(t, T));
        Tprev = T;
    }
    return solutions;
}
