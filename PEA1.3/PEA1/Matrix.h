#pragma once
#include <iostream>


//Klasa poœwiêcona macierzy s¹siedztwa
//Zadania utworzenie macierzy
//Oczdczyt i zapis do pliku
class Matrix
{
public:
	int cities;			//okreœla liczbê miast
	int **matrix;		//WskaŸnik do tablicy dwuwymiarowej, bêdzie reprezentacj¹ macierzy s¹siedztwa
	
	Matrix();
	~Matrix();

	int getCities();
	void setCities(int c);
	void setMatrrix(int cities);

	void addValueToMatrix(int i, int j, int x);
	void showMatrix();
	void showCities();

	void loadFromFile(std::string fileName);
};

