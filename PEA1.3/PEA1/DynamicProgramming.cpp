#include "pch.h"
#include "DynamicProgramming.h"
#include "Matrix.h"
#include "Library.cpp"
using namespace std;

//Konstruktor ustawia atrybuty pomocniczne, dokonuje alokacji tablic dynamicznych
DynamicProgramming::DynamicProgramming(Matrix _matrix, int _startCity)
{
	cities = _matrix.getCities();
	startCity = _startCity;

	matrix = new int *[cities];

	for (int i = 0; i < cities; i++)
	{
		matrix[i] = new int[cities];
		for (int j = 0; j < cities; j++)
		{
			matrix[i][j] = _matrix.matrix[i][j];
		}
	}

	ALL_VISITED = (1 << cities) - 1;
	helpMatrix = new int *[pow(2, cities)];
	tourMatrix = new int *[pow(2, cities)];

	for (int i = 0; i < pow(2, cities); i++)
	{
		helpMatrix[i] = new int[cities];
		tourMatrix[i] = new int[cities];
	}

	for (int i = 0; i < pow(2, cities); i++)
	{
		for (int j = 0; j < cities; j++)
		{
			helpMatrix[i][j] = -1;
			tourMatrix[i][j] = -1;
		}
	}

	bestWay = new int[cities + 1];
	for (int i = 0; i <= cities; i++)
	{
		bestWay[i] = 0;
	}

	lowestCost = TSP(1 << startCity, startCity);
	bestWay = findBestWay();
}

/*//Destruktor zwalnia pamiêæ z tablicy dynamicznych
DynamicProgramming::~DynamicProgramming()
{
	for (int i = 0; i < pow(2, cities); i++)
	{
		for (int j = 0; j < pow(2, cities); j++)
		{
			delete[] helpMatrix[i];
			delete[] tourMatrix[i];

		}
	}
	delete[] helpMatrix;
	delete[] tourMatrix;

	for (int i = 0; i < cities; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] bestWay;
}*/

//Metoda TSP wyszukuje i oblicza koszt najkrótszej œcie¿ki
int DynamicProgramming::TSP(int mask, int position)
{
	if (mask == ALL_VISITED) {
		return matrix[position][startCity];
	}
	if (helpMatrix[mask][position] != -1) {
		return helpMatrix[mask][position];
	}

	int ans = maxINT;
	int nextCity = -1;

	for (int i = 0; i < cities; i++) {

		if ((mask&(1 << i)) == 0) {

			int newAns = matrix[position][i] + TSP(mask | (1 << i), i);
			if (newAns < ans) {
				ans = newAns;
				nextCity = i;
			}
		}
	}
	tourMatrix[mask][position] = nextCity;
	helpMatrix[mask][position] = ans;

	return  ans;
}

//Metoda findBestWay zwraca wskaŸnik na tablicê z najkrótsz¹ œcie¿k¹
int *DynamicProgramming::findBestWay()
{
	int position = startCity;
	int mask = 1 << position;
	bestWay[0] = bestWay[cities] = startCity;

	for (int i = 1; i < cities; i++) {
		bestWay[i] = tourMatrix[mask][position];
		position = bestWay[i];
		mask = mask | (1 << position);
	}
	return bestWay;
}

//Metoda showPath wypisuje œcie¿kê 
void DynamicProgramming::showPath()
{
	cout << "Najlepsza sciezka: ";
	for (int i = 0; i <= cities; i++)
	{
		cout << bestWay[i] << " ";
	}
}

//Metoda showCost wyœwietla koszt œcie¿ki
void DynamicProgramming::showCost()
{
	cout << "Koszt sciezki: " << this->lowestCost << endl;
}

