#pragma once
typedef double (*TPF)(double);
double IntTrap(TPF f, double a, double b, double eps, int& n);
double IntRect(TPF f, double a, double b, double eps, int& n);



double realF1(double a, double b);
double realF2(double a, double b);
double realF3(double a, double b);
double realF4(double a, double b);