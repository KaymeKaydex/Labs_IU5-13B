#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

int GetKeyByWord(string a)
{
	int counter=0;
	for (int i = 0; i < a.length() + 1; i++)
	{
		counter += a[i];
	}
	return counter % 256;
}
void Show(int *a, int n)
{
	cout << "[ ";
	for(int i =0;i<n;i++)
	{
		
		cout << a[i] << ' ';
	}	
	cout << " ]"<<endl;

}

class CodeElement
{
public :
	string path;
	int* Keys;
	size_t Klenght;
	size_t Codirovka;
	string* buff = new string;

	void CodeDecodeTxt()
	{
		SetConsoleCP(1251);

		char* buff = new char();
		fstream* writer = new fstream(path,ios::out | ios::in);
		int i = 0;
		while ((*writer).get(*buff))
		{
			if ((*buff) == '\n') continue;
			(*writer).seekg(-1, ios::cur);
			int a = *buff;
			int b = i % Klenght;
			
			(*writer) << (char)(a^b);
				i++;
				
			(*writer).seekg((*writer).tellg(), ios::beg);

		}
		
		(*writer).close();
		delete buff,i,writer;

	}
	
	void ReadTxt() 
	{
		SetConsoleCP(866);	
		setlocale(LC_ALL, "rus");
		(*buff) = "";
		ifstream* reader = new ifstream(path);
		
		if (!(*reader).is_open())
		{
			cout << "������ ������ �����\n";
			return;
		}
		while (!(*reader).eof())
		{
			getline(   (*reader)	,	(*buff)	);
			
			cout << *buff<<endl;
		}
		(*reader).close();
		delete reader;
		
	}



	CodeElement(string TextPath, int* Keys, int KLenght,int kodirovka)
	{
		path = TextPath;
		this->Keys = Keys;
		this->Klenght = KLenght;
		Codirovka = kodirovka;
	}
	CodeElement() {};
	~CodeElement()
	{
		delete buff;
	}
};


static int menu()
{
	cout <<'\t'<< '\t' << string(10,'=')<<"�������� ��������"<<string(10,'=')<<endl;
	cout << '\t' << "1-�������� ������� ������," << endl;
	cout << '\t' << "2-����������� ���������� �����," << endl;
	cout << '\t' << "3-������������� ������ �� ����� � ������������� �������," << endl;
	cout << '\t' << "4-����� �� ���������."<<endl;
	int res = 0;
	cout << ">>";
	cin >> res;
	while (cin.fail()) {			//���������� ������������ � ������ ����� ������������ ��������
		cout << "������ �����. ��������� ����\n";
		cin.clear();				//����� � ������ ����� ������
		cin.ignore(10, '\n');		//���������� �� ������ ������ ��������� ��������
		cin >> res;				//��������� ����
	}
	return res;
}

int main()
{	
	system("cls");
	setlocale(LC_ALL, "rus");
	int* Keys;											//������ ������, ������� �� ����� ������������ �� �������� ��������

	string delim =" ";									//�����������										
	ifstream CodeNotepad("CodeNotepad.txt", ios::in);	// ������� ������ ifstream , ���� ��������� � ������ ������������
	string buff = "";									//������
	size_t pos = 0;
	string token;										// ���������� substr
	int slovo, count = 0;
	size_t i = 0;										//�������
	
			if (CodeNotepad.is_open() == false)
			{
				cout << "�� ������� ������� ���� CodeNotepad.txt";
			}
			getline(CodeNotepad, buff);				//�������� ������ �� �����

			
			//������� ���������� ���� � ������
			while (buff[i] == ' ' && buff[i] != '\0')
				i++;
			slovo = 0;
			while (buff[i] != '\0') {
				if (buff[i] != ' ' && slovo == 0)
				{
					slovo = 1;
					count++;
				}
				else if (buff[i] == ' ')
					slovo = 0;
				i++;
			}

			cout << "���������� ���� � ������ " << count<<endl;
			Keys = new int[count];

			i = 0;
			
			while ((pos = buff.find(delim)) != string::npos) { //�������� ������ ����� �� �����������
				token = buff.substr(0, pos);
				cout << token << endl;
				buff.erase(0, pos + delim.length());
				Keys[i] = GetKeyByWord(token);
				i++;
			}
			Keys[i] = GetKeyByWord(buff);
			cout << buff << endl;

			cout << "������ ������ : ";
			Show(Keys, count);
			
			CodeElement *DCodeFile = new CodeElement("Text.txt",Keys,count,1251);
			(*DCodeFile).ReadTxt();
			(*DCodeFile).CodeDecodeTxt();
			return 0;
	
	
}

