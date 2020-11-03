#pragma once

#include <iomanip>
#include <iostream>
#include "ShowMatrix.h"
#include <string>
using namespace std;


int Razryad(double a)
{
	int k = (int)a;
	int i = 0;
	while (k > 0)
	{
		k /= 10;
		i++;
	}
	return i;
}
int Razryad(int a)
{
	int k = (int)a;
	int i = 0;
	while (k > 0)
	{
		k /= 10;
		i++;
	}
	return i;
}
int Razryad(long double a)
{
	int k = (int)a;
	int i = 0;
	while (k > 0)
	{
		k /= 10;
		i++;
	}
	return i;
}


template <typename T>
double maxElement(T** a, int nrow, int ncol) {
	double max = NULL;
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			a[i][j] > max ? max = a[i][j] : false;
		}
	}
	return max;
}

template <typename T>
void Show(T** a, int nrow, int ncol, int nZnakov = 0, bool scient = 0)
{
	cout << string(40, '=') << endl;
	int LenghtOfConsole = 80;
	int w = Razryad(maxElement(a, nrow, ncol)) + nZnakov + 5;
	if (scient) w += 3;

	int colInOneStr = LenghtOfConsole / (w);

	for (int l = 0; l < (double)ncol / colInOneStr; l++)
	{		//Печатаем ряд
		for (int j = l * colInOneStr; j < (l + 1) * colInOneStr && j < ncol; j++) {
			if ((j + 1) < 10)
				wcout << setw(w) << L"Ряд " << j + 1;
			else
			{
				wcout << setw(w - 1) << L"Ряд " << j + 1;
			}
		}

		cout << endl;
		for (int i = 0; i < nrow; i++) {
			for (int j = l * colInOneStr; j < (l + 1) * colInOneStr && j < ncol; j++) {
				if (scient)
					cout << setw(w+1) << setprecision(nZnakov) << scientific << a[i][j] << " ";
				else
					cout << setw(w) << setprecision(nZnakov) << fixed << a[i][j] << " ";
			}
			cout << endl;

		}
	}
}
