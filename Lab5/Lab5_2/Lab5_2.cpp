#include <iostream>
#include <string>
#include <iomanip>
#include "Header.h"


using namespace std;

struct Date
{
	int day;		//День
	int month;		//Месяц
	int year;		//Год
};
struct Student
{
	string name;		//Имя сутдента
	Date birthDay;		//День рождения 
	char id[8];			//номер зачётной книжки

	friend ostream& operator<< (std::ostream& out, const Student& person);

};
std::ostream& operator<< (std::ostream& out, const Student& person)
{
	out << person.name << " " << setw(7) << person.birthDay.day << "." << person.birthDay.month << "." << person.birthDay.year << setw(5) << " " << person.id;

	return out;
}


template <typename T>
bool cmp1(T a, T b) { return a.name > b.name; }								// Сортировка по имени
template <typename T>
bool cmp3(T a, T b) { return strcmp(a.id, b.id) > 0;}						//Сортировка по зачетной книжке
template <typename T>														//Сортировка по дате родждения
bool cmp2(T a, T b)
{
	if (a.birthDay.year == b.birthDay.year) {
		if (a.birthDay.month == b.birthDay.month)
		{
			return (a.birthDay.day > b.birthDay.day);
		}
		else return (a.birthDay.month > b.birthDay.month);
	}
	else
	{
		return(a.birthDay.year > b.birthDay.year);
	}
}									//Сортировка по дате

typedef  bool (*CMP)(Student& obj1, Student& obj2);

CMP cmp[3] = { cmp1,cmp2,cmp3 };											//Массив ссылок на функции компаратора(сравнения)






template <typename T>
void BubbleSort1(CMP c, T* Array, unsigned short int lenght = 1) {

	for (int i = lenght - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (c(Array[j], Array[j + 1]))
			{
				auto temp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = temp;

			}

		}
	}
}
template <typename T>
void MaxMinSort(CMP c,T* Array,unsigned short int lenght) {
	Student Tmax = {" ",0,0,0," "};											//Предварительный "Максимальный студент"
	int TmaxIndex;															//Индекс максимального эллемента
	TmaxIndex = 0;															
	for (int i = 0; i < lenght; i++) {
		for (int j = i; j < lenght; j++) {
			if (c(Array[j],Tmax)) {
				Tmax = Array[j];
				TmaxIndex = j;
			}

		}
		Array[TmaxIndex] = Array[i];
		Array[i] = Tmax;
		Tmax = {" ",0,0,0," "};
	}
}




int main()
{
	setlocale(LC_ALL, "Russian");
	
	
	Student group[10] =									// Объявляем и инициализируем группу студентов из 10 человек
	{
		{"Vasya",1,5,2001,"yy43-n"},
		{"Anton",5,7,2002,"1443-r"},
		{"Kolya",3,8,2000,"u243-i"},
		{"Leha",14,12,2005,"1253-u"},
		{"Alex",27,7,2006,"1223-a"},
		{"Senya",10,2,2003,"1143-f"},
		{"Danil",19,12,2000,"1643-k"},
		{"Vova",18,4,2001,"1288-h"},
		{"Anatolii",8,11,2001,"1773-a"},
		{"Peter",10,11,2001,"1343-n"}
	};

	while (true) {
		switch (Menu()) {
		case 1: 
			Show(group,10);
			break; 
		case 2: 
			MaxMinSort(cmp1, group, 10);
			Reverse(group, 10);
			Show(group, 10);
			break;
		case 3:
			MaxMinSort(cmp2, group, 10);
			Reverse(group, 10);
			Show(group, 10);
			break;
		case 4:
			MaxMinSort(cmp3, group, 10);
			Reverse(group, 10);
			Show(group, 10);
			break;
		case 5:
			BubbleSort1(cmp1, group, 10);
			Show(group, 10);
			break;
		case 6:
			BubbleSort1(cmp2, group, 10);
			Show(group, 10);
			break;
		case 7:
			BubbleSort1(cmp3, group, 10);
			Show(group, 10);
			break;
		case 8: return 0;//завершение работы
		default: 
			cout << "Недопустимое действие.Повторите выбор.\n";
			break;
		}
	}

	
}
