#include <iostream>
#include <iomanip>

using namespace std;


struct I_print {
public:				//������ ��� ������ ����������� ��������������
	char name[12];		//�������� �������
	double i_sum;	//�������� ������������ �����
	double i_toch;	//������ �������� ���������
	int n;			//����� ��������� ������� �������������� ��� ������� ���������� ��������� ��������


};

void PrintTabl(I_print i_prn[], int k)
{
	system("chcp 866>nul");
	const int m = 4;//����� �������� �������
	int wn[m] = { 14,20,20,12 };//������ �������� �������
	const char* title[m] = { "Function","Integral","IntSum","N " };
	int size[m];
	for (int i = 0; i < m; i++)
		size[i] = strlen(title[i]);
	//����� �������
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
	{//���������� �������
		cout << char(195) << fixed;
		for (int j = 0; j < m - 1; j++)
			cout << setfill(char(196)) << setw(wn[j]) << char(197);

		cout << setw(wn[m - 1]) << char(180) << setfill(' ') << endl;

		if(i%2!=0)
		cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name << setw((wn[0] - strlen(i_prn[i].name)) / 2) << char(179);
		else 
		cout << char(179) << setw((wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name << setw((wn[0] - strlen(i_prn[i].name)) / 2) <<" "<< char(179);

		cout << setw(wn[1] - 1) << setprecision(10) << i_prn[i].i_toch << char(179)
			<< setw(wn[2] - 1) << i_prn[i].i_sum << char(179)
			<< setw(wn[3] - 1) << i_prn[i].n << char(179) << endl;
	}
	//��� �������
	cout << char(192) << setfill(char(196));
	for (int j = 0; j < m - 1; j++)
		cout << setw(wn[j]) << char(193);
	cout << setw(wn[m - 1]) << char(217) << endl;
	//�������������� �������������� �������� 
	cout << setprecision(6) << setfill(' ');
	system("chcp 1251>nul");
}
