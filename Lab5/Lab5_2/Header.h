#pragma once
#include <string>

struct Date
{
	int day;
	int month;
	int year;
};

						 //���������� �������� �� ������ (������)
template <typename T>
void Show(T* array, unsigned short int lenght = 1) {
	for (int i = 0; i < lenght; i++) {
		std::cout << array[i]<<"\n";
	}
}

						// ��������������� ������� ����
int Menu();

						//����������� ���������� (������) . � �������� ��������� �������� ������ �� ���������� (��� ���������)
