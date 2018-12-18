#pragma once
#include <list>
#include <vector>
using namespace std;

class TabuList
{
public:
	int **tabuList;
	int numberOfCities;
	int cadency;

	TabuList(int numberOfCities, int cadency);
	~TabuList();
	
	void tabuMove(int city1, int city2);
	void decrementTabu();
};

