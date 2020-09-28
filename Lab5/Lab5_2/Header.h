#include <iostream>

using namespace std;

void Randomize(int* Array, int N) {
	for (int i = 0; i <= N; i++) {
		Array[i] = rand() % 100 + 1;
	}
}


bool cmp1(int a, int b) { return a > b; } //для сортировки целочисленного массива по возрастанию;
bool cmp2(int a, int b) { return a < b; };  //для сортировки целочисленного массива по убыванию;
bool cmp(char* a, char* b) { return strcmp(a, b) > 0; } //для сортировки массива из символьных строк по возрастанию;

int BubbleSort(int* Array,int N) {
	int ni = 0;
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
	return ni;
}




template <class T>
void Sort(T array[], int n) {
	T t;
	int cnt;
	for (int i = 0; i < n; i++) {
		cnt = 0;
		for (int j = 0; j < n - 1; j++) { //поменял i на 1 сортирует и выводит без помех, 
			if (cmp(array[j].name.c_str, array[j + 1].name.c_str())) { //а до этого да, вывод максимального был подпорчен
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
				cnt++;
			}
		}
		if (cnt == 0) { break; }
	}
	return;
}

int MaxMinSort(int* Array,int N) {
	int ni = 0;
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
	return ni;
}

void Reverse(int* Array,int N) {
	for (int i = 0; i < N / 2; i++) {
		int temp = Array[i];
		Array[i] = Array[N - i - 1];
		Array[N - i - 1] = temp;
	}
}
void Show(int* Array,int N) {
	for (int i = 0; i < N; i++) {
		cout << Array[i] << " ";
	}
	cout << " " << endl;
}
int Length(char text[]) {
	int arrayLength = 0;
	for (int i = 0; text[i]; i++) {
		arrayLength++;
	}
	return arrayLength;
}
int Rand(int a, int b){
	int diapason = b - a;
	return a + rand() % diapason;
}


