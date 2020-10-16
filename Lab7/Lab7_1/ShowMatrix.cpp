#include <iomanip>
#include <iostream>

using namespace std;


int Razryad(double a) 
{
	int k = (int)a;
	int i = 0;
	while (k>0)
	{
		k /= 10;
		i++;
	}
	return i;
}
double maxElement(double** a, int nrow, int ncol) {
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
void Show(double** a, int nrow, int ncol , unsigned int nZnakov =0, bool scient = 0)
{
	if (scient) nZnakov = 0;

	int w = Razryad(maxElement(a, nrow, ncol))+nZnakov +5;
	if (scient) w += 3;

	int colInOneStr = 105 / (w) ;

	cout << colInOneStr << endl;
	for (int l = 0; l < (double)ncol / colInOneStr; l++)
	{		//Печатаем ряд
		for (int j = l*colInOneStr; j < (l+1)*colInOneStr && j<ncol; j++) {
			if ((j+1)<10)
				wcout << setw(w) << L"Ряд " << j + 1;
			else
			{
				wcout << setw(w-1) << L"Ряд " << j + 1;
			}
		}
		
		cout << endl;
		for (int i = 0; i < nrow; i++) {
			for (int j = l * colInOneStr; j < (l + 1) * colInOneStr && j < ncol; j++) {
				if (scient)
					cout << setw(w)<<setprecision(1) << scientific << a[i][j] << " ";
				else
					cout << setw(w) << setprecision(nZnakov) << fixed << a[i][j] << " ";
			}
			cout << endl;

		}
	}
}

