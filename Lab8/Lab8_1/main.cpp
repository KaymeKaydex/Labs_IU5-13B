#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

int GetKeyByWord(string a)
{
	register int counter=0;
	for (int i = 0; i < a.length() + 1; i++)
	{
		unsigned char tmp = a[i];
		counter += tmp;
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
	cout << "]"<<endl;

}


class CodeElement
{
private :
	const enum const_sizes {w = 5, stats_size = 256};
public :
	string path;
	int* Keys;
	size_t Klenght					=0;
	size_t Codirovka;
	string* buff = new string;
	int stats[2][stats_size];			 //Две таблицы. Статистика для пробела и для введенного символа
	unsigned char char_for_stats				= 97;// Символ для сбора статистики

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
			unsigned char temp = *buff;
			int a = (int)temp;
			int b = Keys[i % Klenght];
			

			// СБОР СТАТИСТИКИ. ПРОВЕРЯЕМ КОДИРУЕМ ЛИ МЫ НУЖНЫЙ СИМВОЛ
			if (temp ==' ')				stats[0][a ^ b]++;
			if (temp == char_for_stats)	stats[1][a ^ b]++;
			//КОНЕЦ СБОРА СТАТИСТИКИ

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

	const enum type_of_stats {backspace=0,my_char=1};
	void ShowStats(type_of_stats tp)
	{
		setlocale(LC_ALL, "rus");
		if (tp == backspace)
			cout << "Statistic for backspace"<<endl;
		else
			cout << "Statistic for symbol " << char(char_for_stats)<<endl;
		cout << char(218)<< string(89, char(196));
		
		cout <<endl<< setw(6)<<char(179);
		for (int i = 0; i < 16; i++)
			cout << setw(w) << i;
		cout <<endl<< string(90, char(196))<<endl;
		for (int i = 0; i < stats_size; i++) 
		{
			if (i % 16 == 0 && i != 0) cout << endl;
			if (i % 16 == 0)cout <<setw(3)<< 16 * (i / 16) << "+ "<<char(179);

			cout << setw(w) << stats[tp][i] ;
		}
		cout << endl << string(90, char(196)) << endl;

	}

	CodeElement(string TextPath, int* Keys, int KLenght,size_t Codirovka,unsigned char char_for_stats)
	{
		//Инициализациия полей в конструкторе
		path					= TextPath;
		this->Keys				= Keys;
		this->Klenght			= KLenght;
		this->char_for_stats	= char_for_stats;
		this->Codirovka			= Codirovka;
		
		//Почистим stats
		for(int j=0;j<2;j++)
		for (int i = 0; i < 256; i++)
			stats[j][i] = 0;
	}
	~CodeElement()
	{
		delete buff;
	}
};


static size_t menu()
{
	cout <<'\t'<< '\t' << string(10,'=')<<"Выберите действие"<<string(10,'=')<<endl;
	cout << '\t' << "1-просмотр массива ключей," << endl;
	cout << '\t' << "2-кодирование/декодирование текстового файла," << endl;
	cout << '\t' << "3-выйти из программы."<<endl;
	int res = 0;
	cout << ">>";
	cin >> res;
	while (cin.fail()) {				//исключение зацикливания в случае ввода недопустимых символов
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

	string delim		=" ";							//Разделитель										
	ifstream CodeNotepad("CodeNotepad.txt", ios::in);	// Создаем объект ifstream , даем директиву и нужное перечисление
	string buff			= "";							//Буффер
	size_t pos			= 0;
	string token;										// Отрезанное substr
	int slovo, count	= 0;
	size_t i			= 0;							//Счетчик
	
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
			
			unsigned char tmp = 'а';
			CodeElement *DCodeFile = new CodeElement("Text.txt",Keys,count,1251,tmp);
			(*DCodeFile).ReadTxt();
			(*DCodeFile).CodeDecodeTxt();
			(*DCodeFile).ShowStats(CodeElement::my_char);
			delete DCodeFile;
			return 0;
			
	
}

