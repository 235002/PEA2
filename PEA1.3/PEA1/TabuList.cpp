#include "pch.h"
#include "TabuList.h"
#include "Library.cpp"


TabuList::TabuList(int numberOfCities, int cadency)
{
	this->numberOfCities = numberOfCities;
	this->cadency = cadency;
	tabuList = new int*[numberOfCities - 2];

	int citiesPerRow = numberOfCities - 2;
	for (int i = 0; i < numberOfCities - 2; i++) {
		tabuList[i] = new int[citiesPerRow];
		citiesPerRow -= 1;
	}
	citiesPerRow = numberOfCities - 1;
	for (int i = 0; i < numberOfCities - 2; i++) {
		citiesPerRow -= 1;
		for (int j = 0; j < citiesPerRow; j++) {
			tabuList[i][j] = 0;
		}
	}
}


TabuList::~TabuList()
{
	for (int i = 0; i < numberOfCities - 2; i++) {
		delete[] tabuList[i];
	}
	delete[] tabuList;
}

void TabuList::tabuMove(int city1, int city2) {
	tabuList[city1][city2] += cadency;
}

void TabuList::decrementTabu() {
	int citiesPerRow = numberOfCities - 1;
	for (int i = 0; i < numberOfCities - 2; i++) {
		citiesPerRow -= 1;
		for (int j = 0; j < citiesPerRow; j++) {
			if (tabuList[i][j] != 0) {
				--tabuList[i][j];
			}
		}
	}
}