
#include <iostream>
#include <math.h>
#include <iomanip>
char on;


using namespace std;


int n ;
double Func(int i =1) {
    if (i == n) {
        return sqrt(n);
    }
    else
    {
        return sqrt(i + Func(i+2));
    }
}

int main()
{
    system("chcp 1251 > nul");
    do {
        
        cout << "Введите n : ";
        cin >> n;
        if (n<0)
        {
            cout << "Введено некоректное значение!" << endl;
            goto bad;
        }
        n = n * 2 + 1;
        cout << "Ответ : " <<setprecision(12)<< Func()<<endl;

       bad: cout << "Продолжить работу? (y/n)\n";
        cin >> on;
    } while (on != 'n');
    return 0;
}
