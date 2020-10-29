#include <iostream>
#include <iomanip>
using namespace std;

int N, ni, swapCounter;


void ShowCounter() {
	cout << "Количество swap >> " << swapCounter << endl;
	cout << "Количество проверок >> " << ni << endl;
}
int Rand(int a, int b) {
	b++;
	return (a + rand() % (b - a));

}		//Функция рандома на отрезке [a,b]
void Randomize(int* Array) {
	for (int i = 0; i <= N; i++) {
		Array[i] = Rand(1, 10);
	}
}

void BubbleSort(int* Array) {

	swapCounter = 0;
	ni = 0;

	int oldlastSwap = 0, lastSwap;
	while (oldlastSwap != -1)
	{
		lastSwap = -1;
		for (int i = N - 1; i > oldlastSwap; i--)
		{
			ni++;
			if (Array[i] < Array[i - 1])
			{

				auto t = Array[i - 1];
				Array[i - 1] = Array[i];
				Array[i] = t;

				swapCounter++;
				lastSwap = i;
			}
		}
		oldlastSwap = lastSwap;
	}

}

void MaxMinSort(int* Array) {
	int max_i, q;
	swapCounter = ni = 0;
	int tempN = N;
	for (int j = 0; j < tempN; tempN--)
	{
		max_i = 0;
		for (int i = 1; i < tempN; i++)
		{
			ni++;
			if (Array[i] > Array[max_i]) max_i = i;
		}
		if (Array[tempN - 1] != Array[max_i])
		{
			swapCounter++;
			q = Array[tempN - 1];
			Array[tempN - 1] = Array[max_i];
			Array[max_i] = q;
		}
	}
}

template <typename T>
void Reverse(T* Array) {
	for (int i = 0; i < N / 2; i++) {
		int temp = Array[i];
		Array[i] = Array[N - i - 1];
		Array[N - i - 1] = temp;
	}
}

void Show(int* Array) {
	/*for (int i = 0; i < N; i++) {
		cout << Array[i] << " ";
	}
	cout << " " << endl;*/
}


int main()
{
	system("chcp 1251 > nul");



	char on = 'y';
	do {
		N = 1;
		cout << "Выберите размер массива>> ";
		cin >> N;
		int* array1;
		array1 = new int[N];
		cout << "Как вы хотите заполнить массив?(1 - вручную, ост. цел значения - автоматически) >> ";
		int type;
		cin >> type;
		if (type == 1) {
			for (int i = 0; i < N; i++) {
				cin >> array1[i];
			}
		}
		else
		{
			Randomize(array1);
		}


		cout << "\n\n====================Пузырьковая сортировка====================" << endl;

		cout << "Перед выполнением сортировки массив был изменен след. образом... \n";
		Show(array1);


		cout << "Сортировка не упорядоченного массива\n";

		BubbleSort(array1);
		Show(array1);
		ShowCounter();


		cout << "Сортировка упорядоченного по возрастанию массива\n";
		cout << "array1[0]: " << array1[0];
		cout << "; array1[9999]: " << array1[N-1] << endl;
		
		array1[N-1] = -1;
		BubbleSort(array1);
		Show(array1);
		ShowCounter();

		cout << "Сортировка упорядоченного по убыванию массива\n";
		Reverse(array1);
		BubbleSort(array1);
		Show(array1);
		ShowCounter();

		cout << "\n\n====================Метод минмального, максимального====================" << endl;
		cout << "Как вы хотите заполнить массив?(1 - вручную, ост. цел значения - автоматически) >> ";
		cin >> type;
		if (type == 1) {
			for (int i = 0; i < N; i++) {
				cin >> array1[i];
			}
		}
		else
		{
			Randomize(array1);
		}
		Show(array1);

		cout << "Сортировка не упорядоченного массива\n";
		MaxMinSort(array1);


		Show(array1);
		ShowCounter();


		cout << "Сортировка упорядоченного по возрастанию массива\n";
		array1[N-1] = array1[0] + 10;
		MaxMinSort(array1);


		Show(array1);
		ShowCounter();

		cout << "Сортировка упорядоченного по убыванию массива\n";
		Reverse(array1);
		MaxMinSort(array1);

		Show(array1);
		ShowCounter();



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
