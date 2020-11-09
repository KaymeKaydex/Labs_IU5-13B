#pragma once
#include <string>



template <typename T>
void Show(T* array, unsigned short int lenght = 1) {
	for (int i = 0; i < lenght; i++) {
		std::cout << array[i]<<"\n";
	}
}

template <typename T>
void Reverse(T* Array, unsigned short int lenght = 1)
{
	for (int i = 0; i < lenght / 2; i++) {
		auto temp = Array[i];
		Array[i] = Array[lenght - i - 1];
		Array[lenght - i - 1] = temp;
	}
}
int Menu();

						
