#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <lagrange.h>
using namespace std;

// Funkcja do obliczania MSE dla danej liczby punktów wêz³owych
double obliczMSE(vector<double>& xi, vector<double>& fi, int liczba_wezlow) {
    if (liczba_wezlow > xi.size() || liczba_wezlow < 2) {
        return INFINITY; // Zwróæ nieskoñczonoœæ dla niepoprawnej liczby wêz³ów
    }

    // Wybierz równoodleg³e punkty wêz³owe
    vector<double> xiWezlowy;
    vector<double> fiWezlowy;

    // Oblicz indeks skoku dla równoodleg³ych punktów
    int skok = (xi.size() - 1) / (liczba_wezlow - 1);
    if (skok < 1) skok = 1;

    // Wybierz wêz³y
    for (int i = 0; i < xi.size() && xiWezlowy.size() < liczba_wezlow; i += skok) {
        xiWezlowy.push_back(xi[i]);
        fiWezlowy.push_back(fi[i]);
    }

    // Upewnij siê, ¿e ostatni punkt jest uwzglêdniony
    if (xiWezlowy.size() < liczba_wezlow && !xi.empty()) {
        xiWezlowy.push_back(xi.back());
        fiWezlowy.push_back(fi.back());
    }

    // Oblicz MSE dla wszystkich punktów
    double mse = 0.0;
    int liczba_punktow = xi.size();

    for (int i = 0; i < liczba_punktow; i++) {
        // Pomiñ punkty, które s¹ wêz³ami
        bool jest_wezlem = false;
        for (int j = 0; j < xiWezlowy.size(); j++) {
            if (abs(xi[i] - xiWezlowy[j]) < 1e-10) {
                jest_wezlem = true;
                break;
            }
        }

        if (!jest_wezlem) {
            double interpolowane = lagrange(xiWezlowy, fiWezlowy, xi[i]);
            double blad = fi[i] - interpolowane;
            mse += blad * blad;
        }
    }

    // Liczba punktów bez wêz³ów
    int punkty_bez_wezlow = liczba_punktow - xiWezlowy.size();
    if (punkty_bez_wezlow > 0) {
        mse /= punkty_bez_wezlow;
    }
    else {
        return 0; // Jeœli wszystkie punkty s¹ wêz³ami, b³¹d jest zero
    }

    return mse;
}

int main() {
    fstream dane;
    dane.open("../../../data/interpolacja_gr_1_INO.txt");
    if (!dane.good()) {
        cout << "brak pliku";
        return 0;
    }
    string line;
    string temp;

    // zapisywanie xi
    vector <double> xi;
    getline(dane, line);
    getline(dane, line);
    istringstream issx(line);
    issx >> temp;
    while (issx >> temp) {
        xi.push_back(stod(temp));
    }
    // zapisywanie f(xi)
    vector <double> fi;
    getline(dane, line);
    istringstream issy(line);
    issy >> temp;
    while (issy >> temp) {
        fi.push_back(stod(temp));
    }

    cout << "Liczba punktow w danych: " << xi.size() << endl;

    // Testuj ró¿ne liczby wêz³ów i zapisz wyniki
    vector<pair<int, double>> wyniki;

    // Testowanie od 2 do liczby wszystkich punktów
    for (int liczba_wezlow = 2; liczba_wezlow <= xi.size(); liczba_wezlow++) {
        double mse = obliczMSE(xi, fi, liczba_wezlow);
        wyniki.push_back({ liczba_wezlow, mse });
        cout << "Liczba wezlow: " << liczba_wezlow << ", MSE: " << mse << endl;
    }

    // ZnajdŸ najmniejszy b³¹d
    auto min_element_it = min_element(wyniki.begin(), wyniki.end(),
        [](const pair<int, double>& a, const pair<int, double>& b) {
            return a.second < b.second;
        });

    cout << "\nOptymalna liczba wezlow: " << min_element_it->first
        << " z MSE: " << min_element_it->second << endl;

    // Przyk³ad u¿ycia optymalnej liczby wêz³ów
    int optymalna_liczba = min_element_it->first;

    // Wybierz równoodleg³e punkty wêz³owe dla optymalnej liczby
    vector<double> xiWezlowy;
    vector<double> fiWezlowy;

    int skok = (xi.size() - 1) / (optymalna_liczba - 1);
    if (skok < 1) skok = 1;

    for (int i = 0; i < xi.size() && xiWezlowy.size() < optymalna_liczba; i += skok) {
        xiWezlowy.push_back(xi[i]);
        fiWezlowy.push_back(fi[i]);
    }

    // Upewnij siê, ¿e ostatni punkt jest uwzglêdniony
    if (xiWezlowy.size() < optymalna_liczba && !xi.empty()) {
        xiWezlowy.push_back(xi.back());
        fiWezlowy.push_back(fi.back());
    }

    // wypisywanie na ekran optymalnych wêz³ów
    cout << "\nOptymalne wezly:\n";
    cout << "xi \t f(xi)\n";
    for (int i = 0; i < xiWezlowy.size(); i++) {
        cout << fixed << setprecision(3) << xiWezlowy[i] << "\t" << fiWezlowy[i] << endl;
    }

    // wpisywanie punktu przez u¿ytkownika
    double x;
    cout << "\nPodaj wartosc punktu do interpolacji: ";
    cin >> x;
    // liczenie wielomianu
    cout << "Wartosc wielomianu w punkcie " << x << ": " << lagrange(xiWezlowy, fiWezlowy, x) << endl;

    // zpisywanie optymalnych wêz³ów do pliku
    ofstream wezly("optymalne_wezly.txt");
    if (!wezly.good()) {
        cerr << "Blad otwarcia pliku" << endl;
        return 1;
    }

    wezly << "xi:";
    for (int i = 0; i < xiWezlowy.size(); i++) {
        wezly << " " << xiWezlowy[i];
    }
    wezly << endl << "fi:";
    for (int i = 0; i < fiWezlowy.size(); i++) {
        wezly << " " << fiWezlowy[i];
    }
    wezly.close();
    dane.close();

    return 0;
}