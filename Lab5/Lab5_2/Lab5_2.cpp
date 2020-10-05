#include <iostream>
#include <string>
#include <iomanip>
#include "Header.h"

using namespace std;


struct Student 
{
	string name;
	Date birthDay;
	char id[8];//номер зачётной книжки

	friend ostream& operator<< (std::ostream& out, const Student& person);

};
std::ostream& operator<< (std::ostream& out, const Student& person)
{
	out << person.name <<" "<<setw(7)<<person.birthDay.day<< "." << person.birthDay.month <<"."<< person.birthDay.year << setw(5) << " "<< person.id;

	return out;
}






Student group[10] =
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

template <typename T>
bool cmp1(T a, T b) { return a.name > b.name; }					// Сортировка по возрастанию
//bool cmp2(int a, int b) { return a < b; };
template <typename T>

bool cmp3(T a, T b) { return a.id > b.id; }	//Сортировка строк

template <typename T>
bool cmp4(T a, T b)
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
}

typedef  bool (*CMP)(Student& obj1, Student& obj2);

// Определяем массив указателей на функции
CMP cmp[3] = { cmp1,cmp3 };


//bool (*cmp[3])(T obj1, T obj2) = { cmp1,cmp3,cmp4 };






template <typename T>
void BubbleSort1(CMP c, T* Array, unsigned short int lenght = 1) {

	for (int i = lenght - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (  c(Array[j] , Array[j + 1]))
			{
				auto temp = Array[j];
					Array[j] = Array[j + 1];
					Array[j + 1] = temp;

			}

		}
	}
}




int main()
{
	setlocale(LC_ALL, "Russian");
	string rt;

	while (true) {
		switch (Menu()) {
		case 1: 
			Show(group,10);
			break; 
		//case 2: 
		//	break;
		//case 3:
		//	break;
		//case 4:0
		//	break;
		case 5:
			
			
			BubbleSort1(cmp4, group, 10);

			break;
		case 6:
			break;
		case 7:
			break;
		case 8: return 0;//завершение работы
		default: 
			cout << "Недопустимое действие.Повторите выбор.\n";
			break;
		}
	}

	
}
