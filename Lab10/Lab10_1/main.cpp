#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include "Print.h"
using namespace std;

enum language {rus, en };


size_t Menu() {

	cout << "================������� MENU===================\n";
	cout << "\t1 - ���������� ���� � �������;\n";
	cout << "\t2 � �������� ���� �� �������; \n";
	cout << "\t3 - ������� ���� � ����������� �� ������� ������� ��������;\n";
	cout << "\t4 - ������� ���� � �������� �� ���������� ������� ��������;\n";
	cout << "\t5 - �������� ������� (����� �� ����� ������� �� ��);\n";
	cout << "\t6 - ����� ������� � ����;\n";
	cout << "\t7 - ������ ������� �� �����;\n";
	cout << "\t8 - ���������� �� ���������� ������\n";
	cout << "\t9 - ������� ���� � ����������� �� ������� �������� �������;\n";
	cout << "\t10 - �����\n";

	size_t choice;
	cout << "�������� ��������\n";
	cin >> choice;
	while (cin.fail()) {//���������� ������������ � ������ ����� ������������ ��������
		cout << "������ �����. ��������� ����\n";
		cin.clear();//����� � ������ ����� ������
		cin.ignore(10, '\n');//���������� �� ������ ������ ��������� ��������
		cin >> choice;//��������� ����
	}
	return choice;
}



const size_t l_word = 31;
const size_t l_dict = 60;


struct Dictionary {


private:
	static int n;
	static bool isSorted;

public:

	static int getN()					{ return n; };
	static void setN(int value)			{ n = value; }

	static bool getIsSorted()			{ return isSorted; }
	static void setIsSortet(bool arg)	{ isSorted = arg; }


	string engl;						// ����� ��-���������
	string rus;							// ����� ��-������
	friend void addWord(Dictionary*);
};
int Dictionary::n = 0;					// ������������� �������� ������������ ����

bool cmp(Dictionary a, Dictionary b)
{
	if (a.engl > b.engl)
		return true;
	return false;
}


void DictionaryFormating(string &str)
{
	for (auto & c : str)
	{
		c = tolower(c);
	}
	str[0] = toupper(str[0]);
};

void showDict(Dictionary *dict)
{
	cout << string(42,'�')<<endl;
	cout <<'|' << setw(10) << "ENG" << setw(20) << "RUS" <<setw(10)<<'|' << endl;
	cout << string(42, '�') << endl;

	size_t Lenght = dict->getN();
	for (size_t i = 0; i < Lenght; i++)
	{
		cout << setw(20) << dict[i].engl << setw(20) << dict[i].rus<<endl;
	}
	cout << string(42, '�') << endl;

}
void addWord(Dictionary* dict) 
{
	//��������� �� ������������ 	
	if (Dictionary::getN() == ::l_dict)
	{
		cout << "������� ��������� ��������.�������� ����� ������!"<<endl;
		return;
	}
	//�������� ���� ���������
	print("Input en/rus words :");
	cin >> dict[dict->getN()].engl >> dict[dict->getN()].rus;
	DictionaryFormating(dict[dict->getN()].engl);
	DictionaryFormating(dict[dict->getN()].rus);
	Dictionary::setN(dict->getN() + 1);
}
void delWord(Dictionary* dict, string word, bool rus = 0)
{
	size_t lenght = dict->getN();

		for (int i = 0; i < lenght; i++)
		{
			if ( rus? dict[i].rus == word: dict[i].engl == word)
			{
				for (int j = i; j < lenght - 1; j++)
				{
					dict[j].rus = dict[j + 1].rus;
					dict[j].engl = dict[j + 1].engl;
				}
				dict->setN(lenght - 1);
				return;
			}
		}
		println("��������� ���� ����� �� �������!");
	
}


void WriteDictionatry(string filename,Dictionary *dict, ios::_Openmode mode = ios::out)
{
	//������ ������� ������� ���������� 
	ofstream *writer = new ofstream(filename,mode);
	size_t dicLenght = Dictionary::getN();
	if ((*writer).is_open() == false) throw exception("���� �� ��� ������");
	for (size_t i=0;i<dicLenght;i++)
	{
		(*writer).write(dict[i].engl.data(),dict[i].engl.length());
		(*writer).put(' ');
		(*writer).write(dict[i].rus.data(), dict[i].rus.length());
		(*writer).put('\n');
	}
	(*writer).close();
	delete writer;
}
void ReadDictionatry(string filename, Dictionary *dict)
{
	//������ �������
	for (size_t i = 0; i < Dictionary::getN();i++)
	{
		dict[i].engl	= "";
		dict[i].rus		= "";
	}
	Dictionary::setN(0);

	//�������� ������
	string buff;

	size_t counterForWords =	0;

	ifstream* reader = new ifstream(filename);
	if (reader->fail()) throw exception();
	while (!(reader->eof()))
	{
		size_t i;
		getline(*reader, buff);

		for (i = 0; i < buff.size(); i++)
		{
			if ((char)buff[i] == ' ') break;
			dict[counterForWords].engl += ((char)buff[i]);
			
		}
		++i;
		for (i; i < buff.size(); i++)
		{
			dict[counterForWords].rus += (buff[i]);
		}
		Dictionary::setN(counterForWords);

		counterForWords++;
	}
}

string translate(Dictionary *dict,string word ,bool from_rus_to_en = 0)
{
	setlocale(LC_ALL, "rus");
	DictionaryFormating(word);
	size_t lenght = dict->getN();
	if (from_rus_to_en) 
	{
		for (int i = 0; i < lenght; i++)
		{
			if (dict[i].rus == word) return dict[i].engl;
		}
	}
	else
	{
		for (int i = 0; i < lenght; i++)
		{
			if (dict[i].engl == word) return dict[i].rus;
		}
	}
	return "����� ����� �� �������!";
}


typedef bool (*CMP)(Dictionary a, Dictionary b);

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


static string BinarySearch(Dictionary *dic, string searched, int start = 0, int end = -1 , language lang= en)
{
	int now;
	string middleValue	= "";
	int middle			= 0;
	switch (lang)
	{
	case en:

		if (end == -1) end = Dictionary::getN() - 1;
		if (start > end)
		{
			//������� �� ������
			return "�� �������";
		}

		////������� ������ ����������
		middle = (end + start) / 2;
		////�������� � ������� ����������
		middleValue = dic[middle].engl;

		if (middleValue == searched)
		{
			return dic[middle].rus;
		}
		else
		{
			if (middleValue > searched)
			{
				//����������� ����� ������ ��� ������ ����������
				return BinarySearch(dic, searched, start, middle - 1);
			}
			else
			{
				//����������� ����� ������ ��� ������� ����������
				return BinarySearch(dic, searched, middle + 1, end);
			}
		}


		break;

	case rus:
		
		if (end == -1) end = Dictionary::getN() - 1;
		now = (end + start) / 2;

		if (dic[now].rus == searched) return dic[now].engl; // ���� �� ����� ���� ������� ���������� ���
		if (start >= end) return "������� ����� �� �������"; // ���� ����� ���� ������� ���������� ����


		if (searched > dic[now].rus)
		{
			return BinarySearch(dic, searched, 0, now);
		}
		else
		{
			return BinarySearch(dic, searched, now + 1, end);
		}

		break;

	}
	

}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");


	Dictionary dict[l_dict];
	string buff		= "";

	

	while (true)
	{
		buff = "";
		switch (Menu() )
		{
		case 1:
			addWord(dict);
			break;
		case 2:
			while( buff!= "rus" && buff != "en")
			{ 
			print("����� ����� �������?(rus/en)");
			cin >> buff;
			}
			
			if (buff == "rus")
			{
				buff = "";
				cin >> buff;
				DictionaryFormating(buff);
				delWord(dict, buff, true);
			}
			else 
			{
				buff = "";
				cin >> buff;
				DictionaryFormating(buff);
				delWord(dict, buff, false);
			}
			break;
		case 3:
			print( "������� �����, ������� �� ������ ��������� : ");
			cin >> buff;
			
			println(translate(dict, buff));
			break;
		case 4:
			print("������� �����, ������� �� ������ ��������� : ");
			cin >> buff;
			println(translate(dict, buff,true));
			break;
		case 5:
			showDict(dict);
			println("");
			break;
		case 6:
			WriteDictionatry("res.txt", dict);
			break;
		case 7:
			ReadDictionatry("res.txt", dict);
			break;
		case 8:
			BubbleSort1(cmp, dict, Dictionary::getN());

			break;
		case 9:
			print("������� �����, ������� �� ������ ��������� : ");
			cin >> buff;
			println(BinarySearch(dict, buff));
			break;		
		case 10:
			return 0;
			break;
		}
	}
	return 0;
}