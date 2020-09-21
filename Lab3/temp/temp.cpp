#include <iostream>
#include <math.h>
#include <iomanip>

#define PI 3.14159265

using namespace std;

int n;
int precision = 7;
int spacing = precision + 4;

long double s_f(long double x)
{
	long double s = 1;
	long double last = 1;

	n = 0;

	while (last > 1e-7)
	{
		long double k = x * x * (2*n+3) / (2*n+1)/(n+1);

		s += k * last;
		last *= k;

		n++;
	}

	return s;
}

long double y_f(long double x)
{
	x = (x * 180) / PI;
	return (1 + 2 * x * x) * exp(x * x);
}

void doPrinting()
{
	for (long double i = 0.0; i <= 1.1; i += 0.2)
	{
		cout << setw(spacing) << i;
		cout << setw(spacing) << y_f(i);
		cout << fixed << setw(spacing) << setprecision(precision) << s_f(i);
		cout << setw(spacing) << n << endl;
	}
}

int main()
{
	system(" chcp 1251 > nul");

	cout << setw(spacing) << "x";
	cout << setw(spacing) << "Y(x)";
	cout << setw(spacing) << "S(x)";
	cout << setw(spacing) << "N" << endl;

	doPrinting();
	cin.ignore();
}

