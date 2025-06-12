#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <nonlinear.h>

using namespace std;

vector<double> exact_f1 = { 0.34807673619718883650 };
vector<double> exact_f2 = { - 1.4841712674141272157716415, 0.033351839749898723120872920, 1.7223257972463175326289883, 3.1179793618188731818774971 };
vector<double> exact_f3 = { - 2.6175341854476564486767068, - 2.3565360645477343049511412, - 1.6508375940959714862803463, - 1.3593350587095296611820025, - 0.96302739518168804171787535, - 0.70942894676404600314799877, - 0.28237468216968630667757767, - 0.054708045885592922719111333, 0.39447532454210036804953917, 0.60289557878005981392989005, 1.0690016102801651307658260, 1.2623850752666164379975495, 1.7419796229893235768857759, 1.9231872558495230327575094, 2.4138626870468130512492661, 2.5849461844017472171809436, 3.0849366939674111952475835, 3.2474276901863970393776121, 3.7553923835710392407056496, 3.9104706068413531938134953 }; // wolfram wypisuje tylko jedno

// Funkcje testowe
double f1(double x) {
    return log(x + 1) -1.0 / (x + 3);
}

double f1_derivative(double x) {
    return 1.0 / (x + 1) + 1.0 / ((x + 3) * (x + 3));
}

double f2(double x) {
    if (abs(x) < EPS) return 1e10; // unikamy dzielenia przez 0
    return x * x * x + 30 * cos(x) -1.0 / x;
}

double f2_derivative(double x) {
    if (abs(x) < EPS) return 1e10;
    return 3 * x * x -30 * sin(x) + 1.0 / (x * x);
}

double f3(double x) {
    return sin(3 * M_PI * x) / (x + 2) + 1.0 / (x + 4);
}

double f3_derivative(double x) {
    double term1 = (3 * M_PI * cos(3 * M_PI * x) * (x + 2) -sin(3 * M_PI * x)) / ((x + 2) * (x + 2));
    double term2 = -1.0 / ((x + 4) * (x + 4));
    return term1 + term2;
}


// Metoda bisekcji

double oblicz_blad_wzgledem_exact(double x, const vector<double>& exact_roots, int j) {
    if (j >= 0 && j < (int)exact_roots.size()) {
        return fabs(x - exact_roots[j]);
    }
    return NAN; // brak dopasowania
}

// Eksport wyników do CSV
void export_to_csv(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i < row.size() -1) file << ",";
        }
        file << "\n";
    }

    file.close();
}

string to_string_precyzyjnie(double value, int precision = 15) {
    ostringstream out;
    out << fixed << setprecision(precision) << value;
    return out.str();
}

int main() {
    vector<vector<string>> results;
    results.push_back({ "Funkcja", "Metoda", "Miejsce_zerowe", "x_obliczone", "x_dokladne", "Blad_bezwzgledny", "Iteracje" });


    // Funkcje i ich nazwy
    double (*functions[])(double) = { f1, f2, f3 };
    double (*derivatives[])(double) = { f1_derivative, f2_derivative, f3_derivative };
    string func_names[] = { "ln(x+1)-1/(x+3)", "x^3+30*cos(x)-1/x", "sin(3*pi*x)/(x+2)+1/(x+4)" };

    cout << fixed << setprecision(15);

    for (int func_idx = 0; func_idx < 3; func_idx++) {
        cout << "\n=== FUNKCJA: " << func_names[func_idx] << " ===\n";

        // Znajdź przedziały ze zmianą znaku
        vector<pair<double, double>> intervals = find_sign_change_intervals(functions[func_idx], -3.0, 4.0, 0.1);

        cout << "Znalezione przedzialy ze zmiana znaku:\n";
        for (const auto& interval : intervals) {
            cout << "[" << interval.first << ", " << interval.second << "]\n";
        }
        const vector<double>& exact_roots = func_idx == 0 ? exact_f1 :
            func_idx == 1 ? exact_f2 : exact_f3;

        // Dla każdego przedziału znajdź miejsce zerowe różnymi metodami
        for (size_t i = 0; i < intervals.size(); i++) {
            double a = intervals[i].first;
            double b = intervals[i].second;
            double mid = (a + b) / 2.0;

            cout << "\nPrzedzial [" << a << ", " << b << "]:\n";

            // Metoda bisekcji
            int iter;
            vector<double> approx;
            double root_bisection = bisection(functions[func_idx], a, b, iter, approx);
            if (!isnan(root_bisection) && i < exact_roots.size()) {
                double x_dokladne = exact_roots[i];
                double blad = fabs(root_bisection - x_dokladne);
                results.push_back({
                    func_names[func_idx],
                    "Bisekcja",
                    to_string(i + 1),
                    to_string_precyzyjnie(root_bisection),
                    to_string_precyzyjnie(x_dokladne),
                    to_string_precyzyjnie(blad),
                    to_string(iter)
                    });
                cout << "Bisekcja: x = " << root_bisection << ", iteracje: " << iter << ", blad: " << blad << "\n";
            }

            
            // Metoda Newtona (analityczna)
            double root_newton = newton(functions[func_idx], derivatives[func_idx], mid, iter, approx);
            if (!isnan(root_newton) && i < exact_roots.size()) {
                double x_dokladne = exact_roots[i];
                double blad = fabs(root_newton - x_dokladne);
                results.push_back({
                    func_names[func_idx],
                    "Newton_analityczna",
                    to_string(i + 1),
                    to_string_precyzyjnie(root_newton),
                    to_string_precyzyjnie(x_dokladne),
                    to_string_precyzyjnie(blad),
                    to_string(iter)
                    });
                cout << "Newton (analityczna): x = " << root_newton << ", iteracje: " << iter << ", blad: " << blad << "\n";
            }

            
            // Metoda Newtona (numeryczna)
            double root_newton_num = newton_numerical(functions[func_idx], mid, iter, approx);
            if (!isnan(root_newton_num) && i < exact_roots.size()) {
                double x_dokladne = exact_roots[i];
                double blad = fabs(root_newton_num - x_dokladne);
                results.push_back({
                    func_names[func_idx],
                    "Newton_numeryczna",
                    to_string(i + 1),
                    to_string_precyzyjnie(root_newton_num),
                    to_string_precyzyjnie(x_dokladne),
                    to_string_precyzyjnie(blad),
                    to_string(iter)
                    });
                cout << "Newton (numeryczna): x = " << root_newton_num << ", iteracje: " << iter << ", blad: " << blad << "\n";
            }

            
            // Metoda siecznych
            double root_secant = secant(functions[func_idx], a, b, iter, approx);
            if (!isnan(root_secant) && i < exact_roots.size()) {
                double x_dokladne = exact_roots[i];
                double blad = fabs(root_secant - x_dokladne);
                results.push_back({
                    func_names[func_idx],
                    "Sieczne",
                    to_string(i + 1),
                    to_string_precyzyjnie(root_secant),
                    to_string_precyzyjnie(x_dokladne),
                    to_string_precyzyjnie(blad),
                    to_string(iter)
                    });
                cout << "Sieczne: x = " << root_secant << ", iteracje: " << iter << ", blad: " << blad << "\n";
            }

            
        }
    }

    // Eksport do CSV
    export_to_csv("wyniki.csv", results);
    cout << "\n\nWyniki zostaly wyeksportowane do pliku wyniki.csv\n";

    // Dodatkowo -szczegółowe dane iteracji dla pierwszych miejsc zerowych każdej funkcji
    cout << "\n=== SZCZEGOLOWE DANE ITERACJI ===\n";

    for (int func_idx = 0; func_idx < 3; func_idx++) {
        vector<pair<double, double>> intervals = find_sign_change_intervals(functions[func_idx], -3.0, 4.0, 0.1);
        int ile_do_zapisania = (func_idx == 0) ? 1 : 2;

        for (int j = 0; j < ile_do_zapisania && j < (int)intervals.size(); ++j) {
            double a = intervals[j].first;
            double b = intervals[j].second;
            double mid = (a + b) / 2.0;

            cout << "\nFunkcja: " << func_names[func_idx] << ", Przedzial: [" << a << ", " << b << "]\n";

            vector<double> approx;
            int iter;

            // ===== Newton (analityczny)
            approx.clear();
            newton(functions[func_idx], derivatives[func_idx], mid, iter, approx);
            vector<vector<string>> data_newton = { { "Iteracja", "x", "f(x)" } };
            for (size_t i = 0; i < approx.size(); ++i)
                data_newton.push_back({ to_string(i), to_string(approx[i]), to_string(functions[func_idx](approx[i])) });
            export_to_csv("iteracje_" + to_string(func_idx) + "_" + to_string(j) + "_newton_a.csv", data_newton);

            // ===== Newton (numeryczny)
            approx.clear();
            newton_numerical(functions[func_idx], mid, iter, approx);
            vector<vector<string>> data_newton_num = { { "Iteracja", "x", "f(x)" } };
            for (size_t i = 0; i < approx.size(); ++i)
                data_newton_num.push_back({ to_string(i), to_string(approx[i]), to_string(functions[func_idx](approx[i])) });
            export_to_csv("iteracje_" + to_string(func_idx) + "_" + to_string(j) + "_newton_num.csv", data_newton_num);

            // ===== Bisekcja
            approx.clear();
            bisection(functions[func_idx], a, b, iter, approx);
            vector<vector<string>> data_bisekcja = { { "Iteracja", "x", "f(x)" } };
            for (size_t i = 0; i < approx.size(); ++i)
                data_bisekcja.push_back({ to_string(i), to_string(approx[i]), to_string(functions[func_idx](approx[i])) });
            export_to_csv("iteracje_" + to_string(func_idx) + "_" + to_string(j) + "_bisekcja.csv", data_bisekcja);

            // ===== Sieczne
            approx.clear();
            secant(functions[func_idx], a, b, iter, approx);
            vector<vector<string>> data_secant = { { "Iteracja", "x", "f(x)" } };
            for (size_t i = 0; i < approx.size(); ++i)
                data_secant.push_back({ to_string(i), to_string(approx[i]), to_string(functions[func_idx](approx[i])) });
            export_to_csv("iteracje_" + to_string(func_idx) + "_" + to_string(j) + "_sieczne.csv", data_secant);
        }
    }


    return 0;
}