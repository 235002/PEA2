#pragma once
#include "Library.cpp"
#include "Matrix.h"

class DynamicProgramming
{
	int ALL_VISITED,
		cities,
		startCity,
		**helpMatrix,
		**tourMatrix,
		**matrix,
		*bestWay,
		maxINT = 999999;

public:
	int lowestCost;
	DynamicProgramming(Matrix matrix, int startCity);
	//~DynamicProgramming();
	int TSP(int mask, int position);
	int *findBestWay();
	void showPath();
	void showCost();
};

