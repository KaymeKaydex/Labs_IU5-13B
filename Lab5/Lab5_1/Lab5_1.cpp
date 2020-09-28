#include <iostream>
#include <iomanip>
using namespace std;

int N,ni;

void Randomize(int* Array) {
	for (int i = 0; i <= N; i++) {
		Array[i] = rand() % 100 + 1;
	}
}

void BubbleSort(int* Array) {
	ni = 0;
	for (int i = N - 1; i >= 1; i--)
		for (int j = 0; j < i; j++)
		{
			if (Array[j] > Array[j + 1])
			{
				int temp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = temp;
				
			}
			ni++;
		}
	
}
void MaxMinSort(int* Array) {
	ni = 0;
	int Tmax = -1, TmaxIndex;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (Array[j] > Tmax) { 
				Tmax = Array[j];
				TmaxIndex = j;
			}
			ni++;
			
		}
		Array[TmaxIndex] = Array[i];
		Array[i] = Tmax;
		Tmax = -1;
	}
}
void Reverse(int* Array) {
	for (int i = 0; i < N/2; i++) {
		int temp = Array[i];
		Array[i] = Array[N - i-1];
		Array[N - i-1] = temp;
	}
}

void Show(int* Array) {		
	for (int i = 0; i < N; i++) {
		cout << Array[i] << " ";
	}
	cout << " " << endl;
}


int main()
{
	system("chcp 1251 > nul");

	char on = 'y';
	do {
		N =1;
		cout << "Выберите размер массива>> ";
		cin >> N;
		int* array;
		array = new int[N];
		cout << "Как вы хотите заполнить массив?(1 - вручную, ост. цел значения - автоматически) >> ";
		int type ;
		cin >> type;
		if (type == 1) {
			for (int i = 0; i < N; i++) {
				cin >> array[i];
			}
		}
		else {
			Randomize(array);
		}
		Show(array);

		cout << "\n\n====================Пузырьковая сортировка====================" << endl;
		BubbleSort(array);
		Show(array);
		cout << "Кол-во иттераций : " << ni;
		cout << "\n\n====================Метод минмального, максимального====================" << endl;
		cout << "Перед выполнением сортировки массив был изменен след. образом... \n";
		Randomize(array);
		Show(array);
		cout << "Отсортированный массив: ";
		MaxMinSort(array);
		Show(array);
		Reverse(array);
		cout << "Проверка реверса\n";
		Show(array);
		cout << "Кол-во иттераций : " << ni;
		// END OF PROGRAM BLOCK

		cout << "\n\nПродолжить работу программы?(y/n) >> ";
		cin >> on;
		while (cin.fail()) {
			cin.clear();
			cout << "Введены некорректные данные, попробуйте снова >> ";
			cin.ignore(10, '\n');
			cin >> on;
		}
		
	} while (on != 'n');
		return 0;
	




}