#include "pch.h"
#include "SimulatedAnnealing.h"
#include "Library.cpp"
using namespace std;

SimulatedAnnealing::SimulatedAnnealing(Matrix matrix, double currentTemp, double cooldownTemp, double minTemp,
	int numberOfIteration)
{
	this->matrix = matrix;
	this->currentTemp = currentTemp;
	this->cooldownTemp = cooldownTemp;
	this->minTemp = minTemp;
	this->numberOfIteration = numberOfIteration;
	
	this->currentRout = new int[matrix.getCities()];
	for (int i = 0; i < matrix.getCities(); i++) {
		currentRout[i] = i;
	}
	this->bestRout = currentRout;
	this->currentRoutLength = routLength(currentRout);
	this->bestRoutLength = currentRoutLength;
	srand(time(NULL));	
}


SimulatedAnnealing::~SimulatedAnnealing()
{
}


void SimulatedAnnealing::findSolution() {
	while (currentTemp > minTemp) {
		for (int i = 0; i < numberOfIteration; i++) {
			random();
			currentRoutLength = routLength(currentRout);

			if ((currentRoutLength < bestRoutLength) || ((double)rand() / (double)RAND_MAX) < probability()){
				bestRout = currentRout;
				bestRoutLength = currentRoutLength;
			}
		}
		currentTemp *= cooldownTemp;
	}
}

double SimulatedAnnealing::routLength(int *rout) {
	double length = 0; 
	for (int i = 1; i < matrix.getCities(); i++) {
		try {
			length += matrix.matrix[rout[i-1]][rout[i]];
		}
		catch (exception e) {
			cout << "Cos poszlo nie tak!" << endl;
		}
	}
	length += matrix.matrix[rout[matrix.getCities()-1]][rout[0]];
	return length;
}

void SimulatedAnnealing::random() {
	int a = rand() % matrix.getCities();
	int b = rand() % matrix.getCities();
	while (a == b) b = rand() % matrix.getCities();

	currentRoutLength = bestRoutLength;
	int tmp = currentRout[a];
	currentRout[a] = currentRout[b];
	currentRout[b] = tmp;
}

double SimulatedAnnealing::probability() {
	return exp(-(currentRoutLength - bestRoutLength) / currentTemp );
}

void SimulatedAnnealing::showRout() {
	cout << "Wyznaczona trasa: ";
	for (int i = 0; i < matrix.getCities(); i++) {
		cout << bestRout[i] << " ";
	}
	cout << endl;
}

void  SimulatedAnnealing::showLength() {
	cout << "Wyznaczony najmniejszy koszt trasy: " << bestRoutLength << " ." << endl;
}

