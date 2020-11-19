#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include "Print.h"
using namespace std;

enum language {rus, en };


size_t Menu() {

	cout << "================СЛОВАРЬ MENU===================\n";
	cout << "\t1 - Добавление слов в словарь;\n";
	cout << "\t2 – Удаление слов из словаря; \n";
	cout << "\t3 - перевод слов с английского на русский методом перебора;\n";
	cout << "\t4 - перевод слов с русского на английский методом перебора;\n";
	cout << "\t5 - просмотр словаря (вывод на экран словаря из ОП);\n";
	cout << "\t6 - вывод словаря в файл;\n";
	cout << "\t7 - чтение словаря из файла;\n";
	cout << "\t8 - Сортировка по английским словам\n";
	cout << "\t9 - перевод слов с английского на русский бинарным поиском;\n";
	cout << "\t10 - Выход\n";

	size_t choice;
	cout << "Выберите действие\n";
	cin >> choice;
	while (cin.fail()) {//исключение зацикливания в случае ввода недопустимых символов
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();//сброс в потоке флага ошибки
		cin.ignore(10, '\n');//извлечение из буфера потока введенных символов
		cin >> choice;//повторный ввод
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


	string engl;						// слово по-английски
	string rus;							// слово по-русски
	friend void addWord(Dictionary*);
};
int Dictionary::n = 0;					// инициализация скрытого статического поля

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
	cout << string(42,'—')<<endl;
	cout <<'|' << setw(10) << "ENG" << setw(20) << "RUS" <<setw(10)<<'|' << endl;
	cout << string(42, '—') << endl;

	size_t Lenght = dict->getN();
	for (size_t i = 0; i < Lenght; i++)
	{
		cout << setw(20) << dict[i].engl << setw(20) << dict[i].rus<<endl;
	}
	cout << string(42, '—') << endl;

}
void addWord(Dictionary* dict) 
{
	//Проверяем на переполнение 	
	if (Dictionary::getN() == ::l_dict)
	{
		cout << "Словарь полностью заполнен.Добавить слово нельзя!"<<endl;
		return;
	}
	//Начинаем само добавлеие
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
		println("Введенное вами слово не найдено!");
	
}


void WriteDictionatry(string filename,Dictionary *dict, ios::_Openmode mode = ios::out)
{
	//Первой строкой запишем количество 
	ofstream *writer = new ofstream(filename,mode);
	size_t dicLenght = Dictionary::getN();
	if ((*writer).is_open() == false) throw exception("Файл не был открыт");
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
	//Чистим словарь
	for (size_t i = 0; i < Dictionary::getN();i++)
	{
		dict[i].engl	= "";
		dict[i].rus		= "";
	}
	Dictionary::setN(0);

	//Начинаем чтение
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
	return "Такое слово не найдено!";
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
			//элемент не найден
			return "Не найдено";
		}

		////средний индекс подмассива
		middle = (end + start) / 2;
		////значение в средине подмассива
		middleValue = dic[middle].engl;

		if (middleValue == searched)
		{
			return dic[middle].rus;
		}
		else
		{
			if (middleValue > searched)
			{
				//рекурсивный вызов поиска для левого подмассива
				return BinarySearch(dic, searched, start, middle - 1);
			}
			else
			{
				//рекурсивный вызов поиска для правого подмассива
				return BinarySearch(dic, searched, middle + 1, end);
			}
		}


		break;

	case rus:
		
		if (end == -1) end = Dictionary::getN() - 1;
		now = (end + start) / 2;

		if (dic[now].rus == searched) return dic[now].engl; // Если мы нашли этот элемент возвращаем тру
		if (start >= end) return "Искомое слово не найдено"; // Если конец стал началом возвращаем фолс


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
			print("Какое слово удалить?(rus/en)");
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
			print( "Введите слово, которое вы хотите перевести : ");
			cin >> buff;
			
			println(translate(dict, buff));
			break;
		case 4:
			print("Введите слово, которое вы хотите перевести : ");
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
			print("Введите слово, которое вы хотите перевести : ");
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