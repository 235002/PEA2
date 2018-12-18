#pragma once
#include "Matrix.h"

class BruteForce
{
public:
	const int maxINT = 2147483647;
	int v0 = 0;
	bool *visited;
	int sptr, shptr;
	int *S, *Sh;
	int n, d, dh;

	BruteForce();
	~BruteForce();
	void przegladZupelny(Matrix matrix, int v0);
	void algorytm(int start, Matrix macierz);
};

