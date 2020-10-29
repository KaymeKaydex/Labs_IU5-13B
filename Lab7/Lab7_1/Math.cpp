int Factorial(int a)
{
	if (a <= 0) {
		return 0;
	}

	if (a == 1)
		return 1;
	else 
	{
		return a * Factorial(a - 1);
	}
}
