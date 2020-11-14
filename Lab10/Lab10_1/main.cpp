#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Dictionary
{
private:
	bool isSorted	= false;
	string rus		="";
	string en		="";
public:
	//Getters and setters
	string	getRus()		{ return rus; };
	string	getEn()			{ return en; };
	bool	getIsSorted()	{ return isSorted; };

	void Sort()
	{
		isSorted = true;

	}
};

void print(Dictionary *dic, size_t lenght)
{
	for (int i = 0; i < lenght;i++)
	{
		cout << dic->getEn() <<" "<<setw(10)<< dic->getRus()<<endl;
	}
}

int main()
{

	return 0;
}