#include "pch.h"
#include "TabuSearch.h"


TabuSearch::TabuSearch()
{
}


TabuSearch::~TabuSearch()
{
}

int* TabuSearch::swap(int city1, int city2, int*solution) {
	int temp = solution[city1];
	solution[city1] = solution[city2];
	solution[city2] = temp;
	return solution;
}

int* TabuSearch::getBestNeighbour(TabuList* tabuList, int* initSolution, int solutionLength, int bestCostGlobal, bool aspiration) {
	int bestCostNeighbourhood = (std::numeric_limits<int>::max)();
	int* bestSolNeighbourhood = new int[solutionLength];
	int newCost = INT_MAX;
	bool aspiResult;

	int city1 = 0;
	int city2 = 0;

	for (int i = 1; i < (solutionLength - 2); i++) {	// mozna chyba zmienic w pierwszej do sollength-2 - dla ostatniej iteracji i i tak niczego nie znajdzie z j
		for (int j = 2; j < (solutionLength - 1); j++) {	// od j=2, zeby ominac zbedna petle dla kazdego
			if (i == j || j < i) {	// j >= i zawsze (wiec np. (1,10) wywolamy, (10,1) nie)
				continue;
			}

			initSolution = swap(i, j, initSolution);
			//newCost = tspEnviromnet->getObjectiveFunctionValue(initSolution, solutionLength);

			// wyszukiwanie najlepszego rozwiazania z sasiedztwa (niezaleznie od tego, czy najlepsze globalnie)
			if (aspiration) {
				aspiResult = ((newCost < bestCostNeighbourhood) && ((tabuList->tabuList[i - 1][j - 1 - i] == 0) || (newCost < bestCostGlobal)));
			}
			else {
				aspiResult = ((newCost < bestCostNeighbourhood) && (tabuList->tabuList[i - 1][j - 1 - i] == 0));
			}

			if (aspiResult) {
				city1 = i;											// odpowiednie wzory na
				city2 = j;											// uzyskanie prawidlowych przejsc (i,j)
				for (int k = 0; k < solutionLength; k++) {			// w tablicy tabuList (iterowanej od 0,
					bestSolNeighbourhood[k] = initSolution[k];		// i,j zaczynaja sie od wartosci 1 i 2!)
				}
				bestCostNeighbourhood = newCost;
			}
			initSolution = swap(i, j, initSolution); //ustawienie initSolution na oryginalna sciezke
		}
	}

	tabuList->decrementTabu();
	tabuList->tabuMove(city1 - 1, city2 - 1 - city1);

	return bestSolNeighbourhood;

}