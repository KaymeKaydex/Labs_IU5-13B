#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	unsigned char c[] = "vishnya";
	unsigned char tmp[] = "гипофиз";
	unsigned char *p = c;

	register size_t count = 0;

	while (*p)
	{
		count += (int)(*p);
		p++;
	}
	cout << "Реальный результат для vishnya" << count % 256 << endl;
	count = 0;
	p = tmp;
	while (*p)
	{
		count += (int)(*p);
		p++;
	}
	cout << "Реальный результат для гипофиз" << count % 256 << endl;
	cout <<"Кодировка для signed "<< (int)'г'<<endl;
	p = tmp;
	cout << "Кодировка для unsigned " << (int)*p<<endl;
	

	
}
