#pragma once
#include <vector>
#include "Matrix.h"
using namespace std;

class SimulatedAnnealing
{
private:
	Matrix matrix;

	int *currentRout;
	int currentRoutLength;
	double currentTemp;
	double cooldownTemp;
	double minTemp;
	int numberOfIteration;

public:
	int bestRoutLength;
	int *bestRout;

	SimulatedAnnealing(Matrix matrix, double currentTemp, double cooldownTemp, double minTemp, int numberOfIteration);
	~SimulatedAnnealing();

	void findSolution();
	double routLength(int *rout);
	void random();
	double probability();
	void showRout();
	void showLength();
};

