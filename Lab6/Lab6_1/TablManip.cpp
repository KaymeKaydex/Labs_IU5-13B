#include <iostream>
#include <iomanip>

using namespace std;


struct I_print {
public:				//данные для печати результатов интегрирования
	char name[12];		//название функции
	double i_sum;	//значение интегральной суммы
	double i_toch;	//точное значение интеграла
	int n;			//число разбиений области интегрирования при котором достигнута требуемая точность


};

void PrintTabl(I_print i_prn[], int k)
{
	system("chcp 866>nul");
	const int m = 4;//число столбцов таблицы
	int wn[m] = { 12,18,18,10 };//ширина столбцов таблицы
	const char* title[m] = { "Function","Integral","IntSum","N " };
	int size[m];
	for (int i = 0; i < m; i++)
		size[i] = strlen(title[i]);
	//шапка таблицы
	cout << char(218) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(194);
	cout << setw(wn[m - 1]) << char(191) << endl;

	cout << char(179);
	for (int j = 0; j < m; j++)
		cout << setw((wn[j] - size[j]) / 2) << setfill(' ') << ' ' << title[j]
		<< setw((wn[j] - size[j]) / 2) << char(179);
	cout << endl;
	for (int i = 0; i < k; i++)
	{//заполнение таблицы
		cout << char(195) << fixed;
		for (int j = 0; j < m - 1; j++)
			cout << setfill(char(196)) << setw(wn[j]) << char(197);

		cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;

		cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name << setw((wn[0] - strlen(i_prn[i].name)) / 2) << char(179);

		cout << setw(wn[1] - 1) << setprecision(10) << i_prn[i].i_toch << char(179)
			<< setw(wn[2] - 1) << i_prn[i].i_sum << char(179)
			<< setw(wn[3] - 1) << i_prn[i].n << char(179) << endl;
	}
	//низ таблицы
	cout << char(192) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(193);
	cout << setw(wn[m - 1]) << char(217) << endl;
	//восстановление первоначальных значений 
	cout << setprecision(6) << setfill(' ');
	system("chcp 1251>nul");
}
