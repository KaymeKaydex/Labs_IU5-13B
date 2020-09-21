#include <iostream>

using namespace std;

char on;



int main()
{
    system(" chcp 1251 > nul");
    do {
        int m, n,sum =0;
        cout << "Введите m и n соответсвенно : ";
        cin >> m >> n;

        if (m >= n) {
            cout << "m >= n . Введите корректные значения! "<< endl;
            goto bad;
        }

        for (int i = 1; i <= n; i++) {
            if (i % 5 == 0 && i % m != 0) sum += i;
        }
        cout << sum<<endl;
    
    
    bad:cout << "Продолжить работу? (y/n)\n";
    cin >> on;
    } while (on != 'n');
    return 0;

}

