#include <iostream>
#include <math.h>
#include <iomanip>

#define PI 3.14159265

using namespace std;

char on;

const int space = 12;

double eps = 0.0000001;

int n =1;


long double Y(double x) {
	
	return x * x * atan(x);
}

long double S(double x)
{
	long double Sum = pow(x, 3);
	long double last = pow(x, 3);
	n =0;
	while (abs(last) > eps) {
		n++;

		long double k = (-pow(x, 2) * (2*n - 1)) / (2*n + 1);
		last *= k;
		Sum += last;
	}
	return Sum;
}

void writer() {
	for (long double i = 0; i <= 1; i += 0.2)
	{
		cout << setw(space) << i;
		cout << setw(space) << Y(i);
		cout << fixed << setw(space) << setprecision(7) << S(i);
		cout << setw(space) << n << endl;
	}
}

void printHorizontalLine() {
	cout << "------------------------------------------------------------" << endl;
}

int main()
{
	system("chcp 1251 > nul");
	do {
	//	cout << "Введите погрешность >> ";
	//	cin >> eps;


		cout << setw(space) << "x";
		cout << setw(space) << "Y(x)";
		cout << setw(space) << "S(x)";
		cout << setw(space) << "N" << endl;
		printHorizontalLine();
		writer();


		printHorizontalLine();
		cout << "Продолжить работу? (y/n)\n";
		
		
		
		if (cin.fail() == false) {cin >> on;
		cin.clear(10);
		cin.get();
		cin.ignore(32767, '\n');
		}
		printHorizontalLine();
	} while (on != 'n');
	return 0;

}
