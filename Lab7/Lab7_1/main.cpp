#include <iostream>
#include <iomanip>
#include "ShowMatrix.h"

using namespace std;





int main()
{
	system("color 2");

	setlocale(LC_ALL, "Russian");
	
	int nrow, ncol;
	cout << "¬ведите число строк и колонок ";
	cin >> nrow >> ncol;
	system("color 7");
	double** a = new double* [nrow];
	for (int i = 0; i < nrow; i++)
		a[i] = new double[ncol];


	for (int i = 0; i < nrow; i++) {
		for (int j = 0; j < ncol; j++) {
			a[i][j] = i + 1.1 + j;
		}
	}

	Show(a, nrow, ncol, 10, 1);


	return 0;
}