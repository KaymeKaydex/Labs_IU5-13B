#include <math.h>

typedef double(*TPF)(double);
double IntTrap(TPF f, double a, double b, double eps, int& n) {
	n = 0;
	double left = f(a);
	double result = 0;
	
	for (double i = a+eps; i <= b; i += eps) {
		result += 0.5 * (left + f(i)) * eps;
		left = f(i);
		n++;
	}
	return result;
}
double IntRect(TPF f, double a, double b, double eps, int& n) {
	n = 0;
	double result = 0;
	for (double i = a; i < b; i += eps) {
		result += f(a) * eps;
		n++;
	}
	return result;
}

double realF1(double a, double b) 
{
	return (b * b - a * a) / 2.0;
}
double realF2(double a, double b)
{
	return (cos(a * 22.0) - cos(b * 22.0)) / 22.0;
}
double realF3(double a, double b)
{
	return (b * b * b * b * b - a * a * a * a * a) / 5.0;;
}
double realF4(double a, double b)
{
	return b * atan(b) - a * atan(a) - (log(b * b + 1) - log(a * a + 1)) / 2.0;
}