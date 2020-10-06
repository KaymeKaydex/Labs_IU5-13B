#include <iostream>
#include <iomanip>
#include <math.h>
#include "MainFunctions.h"
#include "IntegrateFunctions.h"
#include "TablManip.h"
using namespace std;

//Инициализация структуры вне main файла не проходит. Почему?


int main() {
	//Вводим тип алгоритма
	cout << "1 - RiemannSum \n 2- TrapezoidalRule\n";
	cout << "Choose your algorithm >> ";

	int typeOfAlg = 0;
	cin >> typeOfAlg;
	
	typedef double (*Alg)(TPF f, double a, double b, double eps, int& n);

	Alg alg = IntRect;
	switch(typeOfAlg) {
	case(1):
		 alg = IntRect;
		break;
	case(2):
		 alg = IntTrap;
		break;
	}
	//Вводим начало и конец интегрирования
	cout << "Put your a and b >> ";
	double a = -1.0;
	double b = 3.0;
	cin >> a >> b;
	
	I_print table[4] = 
	{
		{"y=x",3.0,3.0,3},
		{"y=sin(22x)",3.0,3.0,3},
		{"y=x^4",3.0,3.0,3},
		{"y=arctg(x)",3.0,3.0,3}
	};
	
	double (*realIntegr[4])(double a, double b) = {realF1,realF2,realF3,realF4};
	double (*funcs[4])(double x) = { f1,f2,f3,f4 };


	for (int i=0;i<5;i++) //Проходимся по таблицам
	{
		for (int j = 0; j < 4; j++) // Проходимся по строкам 1-ой таблицы
		{ 
			table[j].i_sum = alg(funcs[j], a, b, pow(0.1,i+1), table[j].n);
			table[j].i_toch = realIntegr[j](a, b);
		}
		PrintTabl(table, 4);
	}
	
}