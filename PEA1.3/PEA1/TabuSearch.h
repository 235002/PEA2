#pragma once
#include <vector>
#include "TabuList.h"
using namespace std;

class TabuSearch
{
public:
	TabuSearch();
	~TabuSearch();
	int *swap(int city1, int city2, int*solution);
	int *getBestNeighbour(TabuList* tabuList, int* initSolution, int solutionLength, int bestCostGlobal, bool aspiration);
	void printSolution(int *solution, int solutionLength);
};

