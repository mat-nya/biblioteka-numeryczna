#include <iostream>
#include <fstream>
#include <string>
#include "threeintegrations.h"

using namespace std;

int main() {
	string param;
	int N;
	int a, b;

	fstream file("../../../data/kwadratury_gr_1INO.txt", ios::in);
	if (!file.good()) {
		cout << "Error while opening file!";
		return 1;
	}

	file >> param;
	if (param == "N") {
		file >> param; // '='
		file >> N;
	}

	int* A = new int[N+1];

	file >> param;
	if (param == "ai:") {
		for (int i = 0; i < N + 1; i++) {
			file >> A[i];
		}
	}
	
	file >> param;
	if (param == "[a,b]:") {
		file >> a >> b;
	}

	file.close();

	cout << endl << "Calkowanie dla 1 przedzialu:" << endl;
	rectIntegral(a, b, N, 1, A);
	trapIntegral(a, b, N, 1, A);
	SimpsIntegral(a, b, N, 1, A);

	cout << endl << "Calkowanie dla 10 przedzialow:" << endl;
	rectIntegral(a, b, N, 10, A);
	trapIntegral(a, b, N, 10, A);
	SimpsIntegral(a, b, N, 10, A);

	cout << endl << "Calkowanie dla 100 przedzialow:" << endl;
	rectIntegral(a, b, N, 100, A);
	trapIntegral(a, b, N, 100, A);
	SimpsIntegral(a, b, N, 100, A);

	cout << endl << "Calkowanie dla 1000 przedzialow:" << endl;
	rectIntegral(a, b, N, 1000, A);
	trapIntegral(a, b, N, 1000, A);
	SimpsIntegral(a, b, N, 1000, A);

	cout << endl << "Calkowanie dla 10000 przedzialow:" << endl;
	rectIntegral(a, b, N, 10000, A);
	trapIntegral(a, b, N, 10000, A);
	SimpsIntegral(a, b, N, 10000, A);

	delete[] A;
	return 0;
}

