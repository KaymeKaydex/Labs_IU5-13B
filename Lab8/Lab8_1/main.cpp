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
			cout << "Ошибка чтения файла\n";
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
	cout <<'\t'<< '\t' << string(10,'=')<<"Выберите действие"<<string(10,'=')<<endl;
	cout << '\t' << "1-просмотр массива ключей," << endl;
	cout << '\t' << "2-кодирование текстового файла," << endl;
	cout << '\t' << "3-декодирование текста из файла с зашифрованным текстом," << endl;
	cout << '\t' << "4-выйти из программы."<<endl;
	int res = 0;
	cout << ">>";
	cin >> res;
	while (cin.fail()) {			//исключение зацикливания в случае ввода недопустимых символов
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();				//сброс в потоке флага ошибки
		cin.ignore(10, '\n');		//извлечение из буфера потока введенных символов
		cin >> res;				//повторный ввод
	}
	return res;
}

int main()
{	
	system("cls");
	setlocale(LC_ALL, "rus");
	int* Keys;											//Массив ключей, которые мы будем генерировать из кодового блокнота

	string delim =" ";									//Разделитель										
	ifstream CodeNotepad("CodeNotepad.txt", ios::in);	// Создаем объект ifstream , даем директиву и нужное перечисление
	string buff = "";									//Буффер
	size_t pos = 0;
	string token;										// Отрезанное substr
	int slovo, count = 0;
	size_t i = 0;										//Счетчик
	
			if (CodeNotepad.is_open() == false)
			{
				cout << "Не удалось открыть файл CodeNotepad.txt";
			}
			getline(CodeNotepad, buff);				//Получили строку из файла

			
			//Считаем количество слов в строке
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

			cout << "Количество слов в строке " << count<<endl;
			Keys = new int[count];

			i = 0;
			
			while ((pos = buff.find(delim)) != string::npos) { //Получаем каждое слово по отдельности
				token = buff.substr(0, pos);
				cout << token << endl;
				buff.erase(0, pos + delim.length());
				Keys[i] = GetKeyByWord(token);
				i++;
			}
			Keys[i] = GetKeyByWord(buff);
			cout << buff << endl;

			cout << "Массив ключей : ";
			Show(Keys, count);
			
			CodeElement *DCodeFile = new CodeElement("Text.txt",Keys,count,1251);
			(*DCodeFile).ReadTxt();
			(*DCodeFile).CodeDecodeTxt();
			return 0;
	
	
}

