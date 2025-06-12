#ifndef INTEGRACJA_H
#define INTEGRACJA_H

double Horner(int wsp[], int n, double x);
double rectIntegral(int a, int b, int N, int n, int wsp[]);
double trapIntegral(int a, int b, int N, int n, int wsp[]);
double SimpsIntegral(int a, int b, int N, int n, int wsp[]);

#endif
