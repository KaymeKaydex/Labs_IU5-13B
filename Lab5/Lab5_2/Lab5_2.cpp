#include <iostream>
#include <string>
#include <iomanip>
#include "Header.h"



using namespace std;

string names[10] = { "Alex", "Kail","Michel","Maks","Antony","Serega","Leva","Leha","Lexus","Vova" };

const int N = 10;
const int space = 7;

struct Date 
{
	int day;
	int month;
	int year;
};
struct Student 
{
	friend ostream& operator<< (ostream& out, const Student& student); // перегрузка

	string name;
	Date birthDay;
	char id[8];

};
ostream& operator<< (std::ostream& out, const Student& student) {
	out <<setw(space)<< student.name << " " << setw(space)<<student.birthDay.day <<
		'.' << student.birthDay.month << '.' << student.birthDay.year << " "<<
		setw(space) << student.id;
	return out;
} // Перегрузка вывода структуры

void RandomizeStudenst(Student *group) {
	
	for (int i = 0; i < N; i++) {
		group[i].name = names[i];
		group[i].birthDay.day = rand() % 31 + 1;
		group[i].birthDay.month = rand() % 12 + 1;
		group[i].birthDay.year =1900 + rand()%100 ;
		for (int l = 0; l < 6; l++) {
			group[i].id[l] = 192 +rand()%20;
		}
	}
}
void ShowStudents(Student* group) {
		for (int i = 0; i < N; i++) 
		{	
			cout << group[i] << endl;
		}
}

int Menu() {
	cout << "================СОРТИРОВКА МАССИВОВ===================\n";
	cout << "\t1 - Исходный список группы студентов\n";
	cout << "\t2 – miniMax: Сортировка по убыванию даты рождения студента\n";

	cout << "\t5 - bubbleEnd: Сортировка по возрастанию id студента\n";
	cout << "\t8 - Выход\n";
	int choice;
	cout << "Выберите действие\n";
	cin >> choice;
	while (cin.fail()) {//исключение зацикливания в случае ввода недопустимых символов
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();//сброс в потоке флага ошибки
		cin.ignore(20, '\n');//извлечение из буфера потока введенных символов
		cin >> choice;//повторный ввод
	}
	return choice;
}




int main()
{

	system("chcp 1251 > nul");

	Student group[10] = {
		{"Alex",5,7,19,"234y-4"},
		{"Kail",5,7,19,"234y-4"},
		{"Michel",5,7,19,"234y-4"},
		{"Maks",5,7,19,"234y-4"},
		{"Antony",5,7,19,"234y-4"},
		{"Serega",5,7,19,"234y-4"},
		{"Leva",5,7,19,"234y-4"},
		{"Leha",5,7,19,"234y-4"},
		{"Lexus",5,7,19,"234y-4"},
		{"Vova",5,7,19,"234y-4"},
	};

	//RandomizeStudenst(group);

	while (true) {
		switch (Menu()) {
		case 1:
			ShowStudents(group);
			break;//выполнение действия задания 
		case 2:
			Sort(group, 10);
			break;

		case 8:
			return 0;//завершение работы
		default: cout << "Недопустимое действие.Повторите выбор.\n";
		}
	}

	return 0;



}