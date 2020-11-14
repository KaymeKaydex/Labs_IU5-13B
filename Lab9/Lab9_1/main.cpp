#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;


//����� ������
class Matrix
{
private:
    bool isNondegenerate = true;
    bool isSquere = false;
    int  nrow;                      //���������� �����
    int  ncol;                      //���������� �������
public:

    vector<vector<double>> matrix;

    Matrix(double** tmp, int nrow, int ncol)
    {
        this->nrow = nrow; //���������� ����� ������ � ������
        this->ncol = ncol;

        isSquere = (nrow == ncol);



        matrix.resize(nrow);
        for (int i = 0; i < nrow; i++)
            matrix[i].resize(ncol);



        /*matrix[0][0] = 1.0;
        matrix[0][1] = 2.325;*/

        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncol; j++)
                matrix[i][j] = tmp[i][j];
        }

    }
    Matrix(int nrow, int ncol)
    {
        this->nrow = nrow; //���������� ����� ������ � ������
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
        size_t w = 10, presission = 3;
        string name = "";
        cout << "������� ��������� �������" << name << endl;
        for (auto i : matrix) {
            for (auto j : i) {
                cout << fixed << setw(w) << setprecision(presission) << j << " ";
            }
            cout << endl;
        }
    }
    void Show(string name)
    {
        size_t w = 10, presission = 3;
        cout << "������� ��������� ������� " << name << endl;
        for (auto i : matrix) {
            for (auto j : i) {
                cout << fixed << setw(w) << setprecision(presission) << j << " ";
            }
            cout << endl;
        }
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
            cout << "��������� ����������. ���������� ������� ������� A != ���������� ����� ������� B" << endl;
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
            cout << "����� ������ �������� ���� � ����������� �� ������� ���������" << endl;
            throw exception("Uncorrect matrix sum");
        }
        Matrix C(A.nrow, A.ncol);
        for (int i = 0; i < A.nrow; i++)
            for (int j = 0; j < A.ncol; j++)
                C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
        return C;
    }
};

//������� ���������


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

//�������������� �������
void makeAnInverse(Matrix& A)
{
    //�������� �������������� �������� ���� ���������� ��������
    if (A.getIsSquere() == false)
    {
        cout << "Matrix is not squere!";
        throw exception();
    }
    //������� ����������� �������*
    int k = A.getNrow();

    Matrix complemented(k, 2 * k);

    //��������� ����� ������� ������

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            complemented.matrix[i][j] = A.matrix[i][j];

    //���������� ������ ��������� �������
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

    print("��������� ������� ���������� -> ");
    complemented.Show();

    //������ ���. ������ ������� �����������
    for (int i = 0; i < k; i++)
    {
        //���� ������� ������� ����� 0, �� �� ���� !=0 ��� ��� � ������� ����
        if (complemented.matrix[i][i] == 0)
        {
            for (int j = i; j < k; j++)
            {
                if (complemented.matrix[j][i] != 0)
                {
                    complemented.switchRow(i, j);
                    break; //�� ����� ���������, ������ ������ ������ ���
                }
            }
        }
        //���� �� �� ������ ����� ��������� � �� ���� ����� ��� ��� 0 - ������� ���������. ������ ������ � ��������� �� ������
        if (complemented.matrix[i][i] == 0)
        {
            println("������� ���������!");
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
    print("������ ��� -> ");
    complemented.Show();
    //������� ������� �����������. ������ �������� ���

    /*

    �� i ����� ����������� �� �������, �� j ������������� �� ��������
    ����� ������� ������ ����������� �������

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

    print("�������� ��� -> ");
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

    Matrix A(3, 3);
    Matrix B(3, 1);

    A.matrix =
    {
        {1,7,3},
        {-4,9,4},
        {0,3,2}
    };
    A.Show("A");

    B.matrix =
    {
        {-1},
        {0},
        {6}
    };
    B.Show("B");

    makeAnInverse(A);
    A.Show("A , ������� ���� �������������");


    println("��������� � �������. �������� ������� � ���� X1 , X2...Xn");
    Matrix X = A * B;
    X.Show();
    return 0;
}









/*


    int t = 3;
    double** tmp = new double* [t];
    for (int i = 0; i < t; i++)
        tmp[i] = new double[t];


    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t; j++)
            tmp[i][j] = exMatrix[i][j];
    }

    Matrix A(tmp,t,t);
    A.Show();


    Matrix b = A*3;
    b.Show();

    cout << "------------------"<<endl;
    Matrix m1(3,3);
    Matrix m2(3,2);

    m1.matrix =
    {
        {2,5,7},
        {3,9,15},
        {5,16,20}
    };
    m2.matrix =
    {
        {8,1},
        {7,2},
        {2,-3}
    };

    m1.Show();
    cout << string(10,'-');
    m2.Show();

    Matrix m3 =m1*m2;
    m3.Show();
    cout << "------------------"<<endl;
    Matrix m4(2, 2);
    m4.matrix =
    {
        {-5,7},
        {9,8}
    };
    Matrix m4_copy = m4;
    m4_copy.Show();
    println("��������� �������������� ������");
    makeAnInverse(m4);

    println("");

    println("������� ��� � ��� ������");
    println(m4);

    cout << string(10, '-');

    Matrix mres = m4_copy * m4;
    mres.Show();


*/