#include <iostream>
#include <iomanip>
#include "ShowMatrix.h"

using namespace std;





int main() 
{
	system("color 2");
	
	setlocale(LC_ALL, "Russian");
	int nrow, ncol;
	cout << " Введите количество строк и столбцов :";
	cin >> nrow >> ncol;
	system("color 7");
	double** a = new double* [nrow];	
	for (int i = 0; i < nrow; i++)	
		a[i] = new double[ncol];

	
	for (int i = 0; i < nrow; i++) {
		for (int j = 0; j < ncol; j++){
			a[i][j] =i+1.1 ;			
		}
	}

	Show(a, nrow, ncol,2);
	
	
	return 0;
}