#include <math.h>

double abs(double a) {
	if (a > 0) return a;
	return -a;
}

typedef double(*TPF)(double);

double RectIntwithN(TPF f, double a, double b, int n);
double TrapIntwithN(TPF f, double a, double b, int n);


double IntTrap(TPF f, double a, double b, double eps, int& n) {
	register double s = 0;
	n = 1;
	register double s1 = TrapIntwithN(f, a, b, n);
	do {
		s = s1;    
		n *=3;  
		s1 = TrapIntwithN(f, a, b, n);
	} while (fabs(s1 - s) >= (eps/3));
	return s1;
}
double TrapIntwithN(TPF f, double a, double b, int n)
{
	register double  result = 0;
	register double left = f(a);
	register double delX = (b - a) / n;
	for (register double i = a + delX; i <= b; i += delX) //((b - a) / n) - delta x
	{
		result += 0.5 * (left + f(i))*delX;
		left = f(i);
	}
	return result;
}

double IntRect(TPF f, double a, double b, double eps, int& n) {
	register double s = 0;
	n = 1;
	register double s1 = RectIntwithN(f, a, b, n);
	do {
		s = s1;
		n *=3;
		s1 = RectIntwithN(f, a, b, n);
	} while (fabs(s1 - s) >= (eps/3));
	return s1;
}
double RectIntwithN(TPF f, double a, double b, int n) {
	register double delX = (b - a) / n;
	register double result = 0;
	for (register double i = a; i < b; i += delX) {
		result += (f(i) * delX);
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