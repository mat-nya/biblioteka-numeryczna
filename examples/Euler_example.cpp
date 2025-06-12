#include <iostream>
#include <vector>
#include <utility>
#include "Euler.h"

using namespace std;

int main(){
    double steps[] = {0.5, 0.1, 0.01};
    double a = 0.0;
    double b = 9617.0;
    double N;

    for(int i = 0; i < 3; i++){
        double step = steps[i];
        cout << "tKrok = " << step << endl;
        N = (b - a) / step;
        vector<pair<double, double>> solutions = Euler(N, step);
        for(int i = 0; i <= N; i++){
            if(i == 1 || i % 100 == 0 || i == N){
                cout << "t = " << solutions[i].first << ", T = " << solutions[i].second << endl;
            }
        }
        cout << endl;
    }

    return 0;
}

