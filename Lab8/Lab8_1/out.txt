#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;


void Show(static int *a, int n)
{
	cout << "[ ";
	for(int i =0;i<n;i++)
	{
		
		cout << a[i] << ' ';
	}	
	cout << "]"<<endl;

}

void print(string str)
{
	cout << str;
}
void println(string str)
{
	cout << str << endl;
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
	int stats[2][stats_size];						//Две таблицы. Статистика для пробела и для введенного символа
	unsigned char char_for_stats				= 97;// Символ для сбора статистики

	void CodeDecodeTxt()
	{
		SetConsoleCP(1251);

		char* buff = new char();
		fstream* writer = new fstream(path, ios::out | ios::in | ios::binary );

		int i = 0;
		while ((*writer).get(*buff))
		{
			(*writer).seekg(-1, ios::cur);
			register unsigned char temp = *buff;
			register int a = (int)temp;
			register int b = Keys[i % Klenght];
			

			// СБОР СТАТИСТИКИ. ПРОВЕРЯЕМ КОДИРУЕМ ЛИ МЫ НУЖНЫЙ СИМВОЛ
			if (temp ==' ')				stats[0][a ^ b]++;
			if (temp == char_for_stats)	stats[1][a ^ b]++;
			//КОНЕЦ СБОРА СТАТИСТИКИ

			(*writer).put( (char)(a^b) );
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
			cout << "Statistic for symbol " << char_for_stats<<endl;
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
	cout << '\t' << "3-чтение текстового файла," << endl;
	cout << '\t' << "4-выйти из программы."<<endl;
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



int* genKeys(ifstream* codeNoteFile, size_t& lenCodeNote) {
	lenCodeNote = 0;
	char symb;
	while (codeNoteFile->get(symb))
		if (symb == ' ' || symb == '\n')
			lenCodeNote++;

	int* codeNote = new int[lenCodeNote];
	codeNoteFile->clear();
	codeNoteFile->seekg(0, ios_base::beg);

	string wordStr;
	char* word;
	int countWord = 0;
	while (*codeNoteFile >> wordStr) {
		word = (char*)wordStr.c_str();
		int tempRez = 0;
		for (int i = 0; i < wordStr.length(); i++) {
			tempRez += (int)(unsigned char)word[i];
		}
		codeNote[countWord++] = tempRez % 256;
	}
	lenCodeNote = countWord;
	codeNoteFile->close();
	return codeNote;
}


int main()
{	
	system("cls");										// Чистим консоль
	setlocale(LC_ALL, "rus");							//Меняем локаль для вывода русских символов

	int* Keys;											//Массив ключей, которые мы будем генерировать из кодового блокнота

	string delim		=" ";							//Разделитель										
	ifstream CodeNotepad("CodeNotepad.txt", ios::in);	// Создаем объект ifstream , даем директиву и нужное перечисление
	string buff			= "";							//Буффер
	size_t pos			= 0;							//Позиция
	string token;										// Отрезанное substr
	size_t count		= 0;							//Получаем количество слов в счиатанной строке 
	size_t i			= 0;							//Счетчик
	

			Keys = genKeys(new ifstream("CodeNotepad.txt"), count);
			
			print("Введите символ для сбора статистики >>");
			char stat_symbol;
			cin >> stat_symbol;


			CodeElement *DCodeFile = new CodeElement("out.txt",Keys,count,1251, stat_symbol);
			

			setlocale(LC_ALL, "rus");
			SetConsoleCP(866);
			while (true)
			{
				SetConsoleCP(866);
				switch (menu())
				{
				case 1:
					Show(Keys, count);
						break;
				case 2:
					(*DCodeFile).CodeDecodeTxt();
						break;
				case 3:
					(*DCodeFile).ReadTxt();
						break;
				case 4:
					return 0;
						break;
				}
			}


			delete DCodeFile;			
	
}

