void FillInMatrixTask2_2(int** Matrix, int N)
{
	for (int i = 0; i < N; i++)
	{
		Matrix[i][i] = 1;
	}
}