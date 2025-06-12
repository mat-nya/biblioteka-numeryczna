#include <iostream>
#include <iomanip>
#include "threeintegrations.h"

using namespace std;

double Horner(int wsp[], int n, double x){
	if(n == 0) {
		return wsp[0];
	}
	else{
		return x * Horner(wsp, n - 1, x) + (double) wsp[n];
	}
}

double rectIntegral(int a, int b, int N, int n, int wsp[]) {
	double sum = 0.0;
	double dx = (double)(b - a) / (double)n;
	double srodek = a + dx / 2.0;
	for (int i = 1; i <= n; i++) {
		sum += Horner(wsp, N, srodek);
		srodek += dx;
	}
	cout << "Integration using rectangle method: " << fixed << setprecision(6) << sum * dx << endl;
	return sum * dx;
}

double trapIntegral(int a, int b, int N, int n, int wsp[]) {
	double h = (b - a) / (double)n;
	double sum = 0.0;
	double podstawa_a = Horner(wsp, N, a);
	double podstawa_b;
		
	for(int i = 1; i <= n; i++) {
		podstawa_b = Horner(wsp, N, a + h * i);
		sum += (podstawa_a + podstawa_b);
		podstawa_a = podstawa_b;
	}
	cout << "Integration using trapeze method: " << fixed << setprecision(6) << sum * 0.5 * h << endl;
	return sum * 0.5 * h;
}

double SimpsIntegral(int a, int b, int N, int n, int wsp[]) {
	double s = 0;
	double st = 0;
	double dx = (b - a) / (double)n;
	double x;
	for(int i = 1; i <= n; i++) {
		x = a + i * dx;
		st += Horner(wsp, N, x - (dx / 2));
		if(i < n) {
			s += Horner(wsp, N, x);
		}
	}
	double result = dx / 6 * (Horner(wsp, N, a) + Horner(wsp, N, b) + 2 * s + 4 * st);
	cout << "Integration using Simpson's method: " << fixed << setprecision(6) << result << endl;
	return result;
}

