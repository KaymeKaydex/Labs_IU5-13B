#include <iostream>
#include <iomanip>
#include <vector>
#include "PrintMatrix.h";

using namespace std;




//Класс матриц
class Matrix
{
private:
    bool isNondegenerate = true;
    bool isSquere = false;
    int  nrow;                      //Количество рядов
    int  ncol;                      //Количество колонок
public:

    vector<vector<double>> matrix;

    Matrix(double** tmp, int nrow, int ncol)
    {
        this->nrow = nrow; //Объявление полей длинны и ширины
        this->ncol = ncol;

        isSquere = (nrow == ncol);



        matrix.resize(nrow);
        for (int i = 0; i < nrow; i++)
            matrix[i].resize(ncol);


        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncol; j++)
                matrix[i][j] = tmp[i][j];
        }

    }
    Matrix(int nrow, int ncol)
    {
        this->nrow = nrow; //Объявление полей длинны и ширины
        this->ncol = ncol;

        isSquere = (nrow == ncol);


        matrix.resize(nrow);
        for (int i = 0; i < nrow; i++)
            matrix[i].resize(ncol);

        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncol; j++)
                matrix[i][j] = 0;
        }

    }


    void Show()
    {
        ShowMatrix(matrix, nrow, ncol, 3);
    }
    void Show(string name)
    {
        size_t w = 10, presission = 3;
        cout << "Текущее состояние матрицы " << name << endl;
        /*for (auto i : matrix) {
            for (auto j : i) {
                cout << fixed << setw(w) << setprecision(presission) << j << " ";
            }
            cout << endl;
        }*/

        ShowMatrix(matrix, nrow, ncol, 3);
    }


    //Writing getters and setters
    int     getNrow()
    {
        return nrow;
    }
    int     getNcol()
    {
        return ncol;
    }
    bool    getIsSquere()
    {
        return isSquere;
    }
    bool    getIsNondegenerate()
    {
        return isNondegenerate;
    }


    //Logic of Elementary row operations

    void switchRow(int Arow, int Brow)
    {

        for (int i = 0; i < getNcol(); i++)
        {
            auto tmp = matrix[Arow][i];
            matrix[Arow][i] = matrix[Brow][i];
            matrix[Brow][i] = tmp;
        }
    }
    void multiplicateRow(int Arow, double k)
    {
        for (int i = 0; i < getNcol(); i++)
        {
            matrix[Arow][i] *= k;
        }
    }
    void divisionRow(int Arow, double k)
    {
        for (int i = 0; i < getNcol(); i++)
        {
            matrix[Arow][i] /= k;
        }
    }
    void sumRow(int Arow, int Brow)
    {
        for (int i = 0; i < getNcol(); i++)
        {
            matrix[Arow][i] += matrix[Brow][i];
        }
    }
    void subtractionRow(int Arow, int Brow)
    {
        for (int i = 0; i < getNcol(); i++)
        {
            matrix[Arow][i] -= matrix[Brow][i];
        }
    }
    void subtractionRow(int Arow, int Brow, double k)
    {
        for (int i = 0; i < getNcol(); i++)
        {
            matrix[Arow][i] -= matrix[Brow][i] * k;
        }
    }

    //Friend operators
    friend Matrix operator*(const double val, Matrix M)
    {
        for (int i = 0; i < M.nrow; i++)
        {
            for (int j = 0; j < M.ncol; j++)
                M.matrix[i][j] = M.matrix[i][j] * val;
        }
        return M;
    }
    friend Matrix operator*(Matrix M, const double val)
    {
        for (int i = 0; i < M.nrow; i++)
        {
            for (int j = 0; j < M.ncol; j++)
                M.matrix[i][j] = M.matrix[i][j] * val;
        }
        return M;
    }
    friend Matrix operator*(Matrix A, Matrix B)
    {
        if (A.ncol != B.nrow)
        {
            cout << "Умножение невозможно. Количество колонок матрицы A != количеству рядов матрицы B" << endl;
            throw exception("Uncorrect matrix multiplication");
        }
        Matrix C(A.nrow, B.ncol);
        for (int i = 0; i < C.nrow; i++)
            for (int j = 0; j < C.ncol; j++)
            {
                double sum = 0;
                for (int t = 0; t < A.ncol; t++)
                {
                    sum += A.matrix[i][t] * B.matrix[t][j];
                }

                C.matrix[i][j] = sum;
            }
        return C;
    }
    friend Matrix operator+(Matrix A, Matrix B)
    {
        if (A.nrow != A.ncol || B.ncol != B.nrow || A.nrow != B.nrow)
        {
            cout << "Сумма матриц возможна лишь с одинаковыми по размеру матрицами" << endl;
            throw exception("Uncorrect matrix sum");
        }
        Matrix C(A.nrow, A.ncol);
        for (int i = 0; i < A.nrow; i++)
            for (int j = 0; j < A.ncol; j++)
                C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
        return C;
    }
};

//Функции печатания


template <typename T>
void println(T a)
{
    cout << a << endl;
}
void println(Matrix a)
{
    a.Show();
    cout << endl;
}

template <typename T>
void print(T a)
{
    cout << a;
}
void print(Matrix a)
{
    a.Show();
}
void print(double** a, int nrow, int ncol)
{
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
            cout << setw(3) << a[i][j];
        cout << endl;
    }
}

//Инвертирование матрицы
void makeAnInverse(Matrix& A)
{
    //Операция инвертирования доступна лишь квадратным матрицам
    if (A.getIsSquere() == false)
    {
        cout << "Matrix is not squere!";
        throw exception();
    }
    //Создаем дополненную матрицу*
    int k = A.getNrow();

    Matrix complemented(k, 2 * k);

    //Заполняем новую матрицу старой

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            complemented.matrix[i][j] = A.matrix[i][j];

    //Дописываем справа единичную матрицу
    for (int i = 0; i < k; i++)
        for (int j = k; j < 2 * k; j++)
            if (i == j % k)
            {
                complemented.matrix[i][j] = 1;
            }
            else
            {
                complemented.matrix[i][j] = 0;
            }

    print("Дополнили матрицу единичками -> ");
    complemented.Show();

    //Прямой ход. Делаем матрицу треугольной
    for (int i = 0; i < k; i++)
    {
        //Если текущий элемент равен 0, то мы ищем !=0 под ним и свапаем ряды
        if (complemented.matrix[i][i] == 0)
        {
            for (int j = i; j < k; j++)
            {
                if (complemented.matrix[j][i] != 0)
                {
                    complemented.switchRow(i, j);
                    break; //Мы нашли ненулевой, дальше искать смысла нет
                }
            }
        }
        //Если мы не смогли найти ненулевой и на этом месте все еще 0 - матрица вырождена. Выдаем ошибку и сообщение об ошибке
        if (complemented.matrix[i][i] == 0)
        {
            println("Матрица вырождена!");
            throw exception();
        }

        if (i != k - 1)
        {
            complemented.divisionRow(i, complemented.matrix[i][i]);
            for (int tmp = i + 1; tmp < k; tmp++)
            {
                complemented.subtractionRow(tmp, i, complemented.matrix[tmp][i]);
            }
        }
        else
        {
            complemented.divisionRow(i, complemented.matrix[i][i]);
        }


    }
    print("Прямой ход -> ");
    complemented.Show();
    //Сделали матрицу треугольной. Теперь обратный ход

    /*

    По i будем проходиться по строкам, по j соответсвенно по столбцам
    Чтобы уловить логику используйте отладку

    */

    for (int i = 0; i < k; i++)
    {
        if (i != k - 1)
        {
            for (int tmp = i + 1; tmp < k; tmp++)
            {
                complemented.subtractionRow(i, tmp, complemented.matrix[i][tmp]);
            }
        }

    }

    print("Обратный ход -> ");
    complemented.Show();

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A.matrix[i][j] = complemented.matrix[i][j + k];
        }
    }
}


int main()
{
    setlocale(LC_ALL, "rus");

    Matrix A(2, 4);
    Matrix B(4, 2);

    A.matrix =
    {
        {1,2,1,3},
        {4,-1,5,-1}
    };
    A.Show("A");

    B.matrix =
    {
        {1,4},
        {2,-1},
        {1,5},
        {3,-1}

    };
    B.Show("B");
    //makeAnInverse(A);
    A.Show("A , которая была инвертирована");


    println("Переходим к решению. Исходная матрица и есть X1 , X2...Xn");
    Matrix X = A * B;
    X.Show();
    return 0;
}
