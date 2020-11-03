#include <iostream>
#include <iomanip>

#include "PrintMatrix.h" 

using namespace std;

int sign(int a) 
{
	if (a == 0) return 0;
	return (a > 0) ? 1 : -1;
}


const int B[10][10] = { 
						0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
						10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
						20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
						30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
						40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
						50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
						60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 
						70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 
						80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 
						90, 91, 92, 93, 94, 95, 96, 97, 98, 99 
};
const int* pB[] = { B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7], B[8], B[9] }; //массив указателей на массивы 
const int x = 1.0; // из методички

int menu()
{
	cout << *(*(B + 2)+2);
	cout << "================ВЫВОД МАТРИЦ===================\n";
	cout << "\t1 - Вывод матрицы А\n";
	cout << "\t2 – Вывод матрицы B\n";
	cout << "\t3 - Выход\n";
	int choice;
	cout << "Выберите действие\n";
		cin >> choice;
	while (cin.fail()) {			//исключение зацикливания в случае ввода недопустимых символов
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();				//сброс в потоке флага ошибки
		cin.ignore(10, '\n');		//извлечение из буфера потока введенных символов
		cin >> choice;				//повторный ввод
	}
	return choice;

}







int main()
{	
	double** A; // Матрица А
	setlocale(LC_ALL, "Russian");
	while (true) {
		switch (menu()) {
		case 1:
			int N;
			cout << "Введите N:";
			cin >> N;
			bool scient;
			cout << "В каком виде вывести матрицу?\n 0 - Fixed \n 1 - Scientific\n";
			cin >> scient;
			cout << "Введите кол-во знаков после запятой : ";
			int nZnakov;
			cin >> nZnakov;
			A = new double* [N];
			for (int i = 0; i < N; i++)
				A[i] = new double[N];

			A[0][0] = -x;

			A[0][1] = x / 2.0;
			for (int j = 2; j < N; j++)
				A[0][j] = A[0][j - 1] / (j + 1);

			
			for (int i = 1; i < N; i++) {
				
				A[i][0] = A[i - 1][0] * -x;
				
				for (int j = 1; j < N; j++) {
					
					if (j >= i) {
						A[i][j] = A[i - 1][j] * A[0][j];
					}
					else {
						
						A[i][j] = abs(A[i - 1][j] * A[0][j]) * sign(A[i][0]);
					}
				}
			}
			for (int i = 0; i < N; i++)
				A[i][i] = 1;

			Show(A, N, N, nZnakov, scient);
			
			break;		 
		case 2:
			Show(pB, 10, 10);
			break;
		case 3:
			return 0;	//завершение работы
		
		default:
			cout << "Недопустимое действие.Повторите выбор.\n";
		}
		
	}

	
}


