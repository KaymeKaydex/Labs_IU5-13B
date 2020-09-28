#include <iostream>
#include <math.h>
#include <tuple>
#include <string>
using namespace std;



int n , eps = 0.00000001;
const int Nmax = 10000;

static int Sign(double a) {
    if (a == 0) return 0;
    if (a > 0) return 1;
    return -1;
}
static int Sign(int a) {
    if (a == 0) return 0;
    if (a > 0) return 1;
    return -1;
}
static int Sign(float a) {
    if (a == 0) return 0;
    if (a > 0) return 1;
    return -1;
}



//TASK 1
double FunctionTask1(long double x, long double k) {
    return x - k * cos(x);
}
double DerivativeFunctionTask1(long double x, long double k) {
    return 1 + k * sin(x);
}
double Neuwton(int k = 1, int x0 = 1) {
    
    n = 0;
    int TempN= 0;
    
    double nextX, lastX ;
    nextX = lastX = x0;
    while (abs(nextX - lastX) > eps || TempN == 0) {
        if (n > Nmax) {
            cout << "n> Nmax"<< endl;
            break;
        }
        TempN++;
        lastX = nextX;
        nextX -= (FunctionTask1(lastX, k) / DerivativeFunctionTask1(lastX,k));
    }
    n = TempN;
    
   

    return nextX;
}
//END OF TASK 1-2
 

//TASK 3
long double BisectionMethod(double Xn, double Xk, long double k) {
    if (FunctionTask1(Xn, k) == 0) return Xn;
    if (FunctionTask1(Xk, k) == 0) return Xk;
    double Xi = 0;
    n = 0;
    while (Xk - Xn > eps && n < Nmax){
        Xi = Xn + ((Xk - Xn) / 2);

        if (Sign(FunctionTask1(Xn, k)) != Sign(FunctionTask1(Xi, k))) {
            Xk = Xi;
        }
        else Xn = Xi;
        n++;
    }
    return Xi;
}
//END OF TASK 3

//Task 4
double SimpleIteration(double x0) {
    double next = x0;
    double current = x0;
    n = 0;
    while ((abs(current - next) > eps) || (n == 0))
    {
        n++;

        current = next;
        next = current - FunctionTask1(current,1);
    }
    return next;
}
//END OF TASK 4




int main()
{    
    setlocale(LC_ALL, "Russian");

    cout << "Введите соответсвующую задачу Лабораторной работы #4  >> " ;
    int typeOfTask;
    cin >> typeOfTask;

    switch (typeOfTask)
    {
    case 1:
        cout << "Полученный результат  >> " << Neuwton() << endl;
        cout << "Результат получен шагом номер >> " << n << endl;
        break;
    case 2:
        cout << "Введите входные данные в формате k x0 eps >> ";
        int a, b, c;
        cin >> a >> b >> c;
        eps = c;
        cout << "Полученный результат  >> " << Neuwton(a,b) << endl;
        cout << "Результат получен шагом номер >> " << n << endl;
        break;
    case 3:
        cout << "Метод половинного деления\n";
        double Xn, Xk, k;
        Xn = Xk = k = 0;

        cout << "Введите Xn >> ";
        cin >> Xn;

        cout << "Введите Xk >> ";
        cin >> Xk;

        cout << "Введите k >> ";
        cin >> k;

        cout << "Полученный результат  >> " << BisectionMethod(Xn,Xk,k) << endl;
        cout << "Результат получен шагом номер >> " << n << endl;
        break;
    case 4:
        cout << "Метод простых иттераций\n";
        cout << "Введите X0 >> ";
        int x0;
        cin >> x0;
        cout << "Результат >> " << SimpleIteration(x0) << endl;
        cout << "Результат получен шагом номер >> " << n << endl;

        break;
        default:
            string input;
            cout << "Введеты недопустимые значения. Попробовать снова?(Если нет - оставьте поле пустым)\n";
            cin >> input;
            if (input[0]) main();
            break;
        
    }
    return 0;
}


