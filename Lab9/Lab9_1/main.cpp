#include <iostream>
#include <vector>
using namespace std;

class Matrix
{	
private:

	size_t N			=0;
	bool IsComplemented	=0;

	vector <vector <int>> matrix;

	void complement()
	{
													//Создадим единичную матрицу N на N
		int** n = new int* [N];
		for (size_t i = 0; i < N; i++)				//Объявление 
			n[i] = new int[N];

		for (size_t i = 0; i < N; i++)				//Заполнение диагонали
			for (size_t j = 0; j < N; j++)
				if (j == i)n[j][i] = 1;

		delete[] n;
	}
public:
	

	Matrix(vector <vector <int>> matrix, size_t N,const bool complement=1)
	{
		
		this->matrix	= matrix;
		this->N			= N;
		if (complement) this->complement();
	}

	Matrix(int** matirx, size_t N, const bool complement = 1)
	{
		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < N; j++)
				this->matrix[i][j] = matrix[i][j];

		this->N = N;
		if (complement) this->complement();
	}
	

};

int main()
{
	


	return 0;
}