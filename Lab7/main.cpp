#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>

using namespace std;

const int width = 80; //Ширина строки консоли
const int x = 1.0; //x из ТЗ

//Задаем B оператором описания
const int B[10][10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99}; 
const int* arrOfArrB[] = {B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7], B[8], B[9]}; //Массив массивов
int BN = sizeof(B) / sizeof(B[0]); //Высота
int BM = sizeof(B[0]) / sizeof(B[0][0]); //Ширина

//Функция для ввода и возможной проверки данных
int input(string massage, bool (*check)(int, int) = [](int b, int a) {return true;}, int a = -1) {
	int ret;
	
	cout << massage << ": ";
	if (!(cin >> ret) || !check(ret, a)) {
		cout << "Введены некорректные данные" << endl;
		if (cin.fail()) {
			cin.clear();
			while (cin.get() != '\n');
		}
		return(input(massage, check, a));
	}
	return ret;
}
bool checkPositive(int ans, int) { return ans > 0; }
bool checkMenu(int ans, int len) { return ans > 0 && ans <= len; }

//Функция для создания меню
int menu(const string options[], int len, string header, string invite, int start = 0) {
	cout << string(40, '=') << endl;
	cout << header << endl;
	for (int i = start; i < len; i++) {
		cout << i + 1 - start << ") " << options[i] << endl;
	}
	return input(invite, checkMenu, len) + start;
}

//Функция печати матрицы
template <typename T>
void printMatrix(T** arrOfArrMatrix, int N, int M, int eps, bool fixedOrScience) {
	int w = eps + 4; //Ширина столбца
	if (!fixedOrScience) w += 5;
	
	int columns = width / w; //Кол-во столбцов в строке консоли
	int start = 0; //Кол-во выведенных столбцов
	
	//Если столбцов в матрице меньше, чем можно вывести в одной строке
	if (M < columns) {
		//Занимаем всю строку столбцами
		w = width / M;
		//Заменяем кол-во столбцов в консоли на их кол-во в матрице
		columns = M;
	}
	
	//Пока не выведем все столбцы
	while (start < M) {
		//Разграничиваем фрагменты матрицы
		cout << string(width, '-') << endl;
		
		//Проходим по строкам матрицы
		for (int i = 0; i < N; i++) {
			/*Проходим по столбцам от того, что мы не вывели
			 *И до того, что поместиться в строке консоли
			 *Или до конца строки матрицы*/
			for (int j = start; j < min(start + columns, M); j++) {
				//Выводим в нужном формате
				cout << (fixedOrScience ? fixed : scientific) << setw(w) << setprecision(eps) << *(arrOfArrMatrix[i] + j);
			}
			cout << endl;
		}
		//Добавляем выведенные столбцы
		start += columns;
		//Отделяем фрагмент
		cout << string(width, '-') << endl;
	}
}

int sign(int a) { return a == 0 ? 0 : a > 0 ? 1 : -1;}

//Варианты в меню
const string mainMenu[] = {"Вывести A", "Вывести B"};
const string menuFixOrSci[] = {"Scientific", "Fixed"};

int main() {
	//Вывод A или B
	int choose = menu(mainMenu, 2, "Главное меню", "Выберите действие");
	
	if (choose == 2) { //Вывод B
		printMatrix(arrOfArrB, BN, BM, 0, true);
		return(0);
	}
	//Ввод формата вывода и кол-ва цифр
	bool fixOrSci = menu(menuFixOrSci, 2, "Формат вывода", "Выберите формат") - 1;
	int eps = input("Введите кол-во цифер при выводе", checkPositive);
	
	//Ввод размера матрицы для генерации
	int N = input("Введите размер матрицы A", checkPositive);
	
	//Создаем A как массив массивов
	double **A = new double *[N];
	for (int i = 0; i < N; i++) 
		A[i] = new double[N];
	
	A[0][0] = -x; // см 110 строку
	
	//Вручную генерируем первую строку
	A[0][1] = x / 2.0;
	for (int j = 2; j < N; j++) 
		A[0][j] = A[0][j-1] / (j+1);
	
	//Генерируем остальное, кроме главной диагонали
	for (int i = 1; i < N; i++ ) {
		/*Так как первый столбец, кроме 1 элемента
		 *весь находится под главной диагональю,
		 *его можно использовать как эталон знака
		 *в текущей строке для элемент. под глав. диагональю
		 *Каждый следующий элемент в столб. будет иметь
		 *противоположный знак. Однако, 
		 * (-x)^2 = x => A[0][0] должно быть = -x
		 */
		A[i][0] = A[i-1][0] * -x;
		//Проходим по строкам
		for (int j = 1; j < N; j++) {
			//Элемент над главной диагональю?
			if (j >= i) {
				/*Так как следующий элемент в столбце отличается
				 *от предыдущего лишь большей на 1 степенью,
				 *можно представить следующий элем. в столб. как
				 *предыдущий элем. * знач под степенью
				 *А знач. под степенью = 1 элементу в столбце, ведь
				 *там степень (i) = 1*/
				/*Также, так как выше элемента над глав. диаг.
				 *могут быть только такие же элементы, модуль можно не ставить*/
				A[i][j] = A[i-1][j] * A[0][j];
			} else {
				/*Так как элементы над глав. диаг. и под ней могут
				 *отличаться только знаком, берем значение предыдущего
				 *элемента и ставим знак эталона*/
				A[i][j] = abs(A[i-1][j] * A[0][j])*sign(A[i][0]);
			}
		}
	}
	//Заменяем диагональ в самом конце, чтобы в предыдущем цикле
	//Она не мешала опираться на предыдущ. знач. в столбце
	for (int i = 0; i < N; i++)
		A[i][i] = 1;
	//Выводим матрицу
	printMatrix(A, N, N, eps, fixOrSci);
}
