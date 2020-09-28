#include <iostream>
#include <iomanip>

using namespace std;

char on;

int main()
{
    system("chcp 1251 > nul");
    do {
        double a,s;
        a = s = 1;
        cout << "Введите a : ";
        cin >> a;


        if (a >= 0) {
            for (int i = 2; i <= 8; i += 2) {
                s *=( i * i );
            }
            s -= a;
        }
        else {
            for (int i = 3; i <= 9; i += 3) {
                s *= (i - 2);
            }
        }
        cout << setprecision(20)<< s << endl;
        

    cout << "Продолжить работу? (y/n)\n";
        cin >> on;
    } while (on != 'n');
    return 0;

}
