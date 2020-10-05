#pragma once
#include <string>

struct Date
{
	int day;
	int month;
	int year;
};

						 //Показываем элементы по ссылке (шаблон)
template <typename T>
void Show(T* array, unsigned short int lenght = 1) {
	for (int i = 0; i < lenght; i++) {
		std::cout << array[i]<<"\n";
	}
}

						// Предопределение функции МЕНЮ
int Menu();

						//Пузырьковая сортировка (шаблон) . В качестве параметра передаем ссылку на компаратор (вид сравнения)
