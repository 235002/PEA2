#include "pch.h"
#include "Matrix.h"
#include "Library.cpp"
using namespace std;

//Konstruktor ma za zadanie utworzyæ tablicê dwuwymiarow¹
//Ma ona odpowiadaæ macierzy s¹siedztwa i wype³niona zosatnie zerami
Matrix::Matrix()
{
	this->cities = 0;
	this->matrix = new int*[0];
}

//Destruktor Macierzy s¹siedztwa
//Zwalnia pamiêæ po macierzy
Matrix::~Matrix()
{
	/*for(int i = 0; i < cities; i++)
		delete[] matrix[i];
	delete[] matrix;
	matrix = NULL;*/
}

//Setter Maicerzy
void Matrix::setMatrrix(int cities)
{
	setCities(cities);
	matrix = new  int *[cities];

	for (int i = 0; i < cities; i++)
	{
		matrix[i] = new int[cities];
		for (int j = 0; j < cities; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

//Getter atrybutu cities
int Matrix::getCities()
{
	return this->cities;
}

//Setter arybutu cities
void Matrix::setCities(int c)
{
	this->cities = c;
}

//Dodanie wartoœci do Macierzy
void Matrix::addValueToMatrix(int i, int j, int x)
{
	matrix[i][j] = x;
}

//Wyœwietlanie wartoœci macierzy
void Matrix::showMatrix() {
	cout << "     ";
	for (int l = 0; l < cities; l++)
	{
		cout << l << "  ";
	}
	cout << endl;
	for (int l = 0; l < cities; l++)
	{
		cout << "---";
	}
	cout << endl;
	
	for (int i = 0; i < cities; i++) {
		cout << i << " |  ";
		for (int j = 0; j < cities; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//Wyœwietlanie liczby miast
void Matrix::showCities()
{
	cout << endl << "------------------------" << endl;
	cout << "Liczba miast wynosi: " << getCities() << endl;
	cout << "-------------------------" << endl;
}

//Metoda wczytuje dane z pliku do macierzy
void Matrix::loadFromFile(string fileName)
{
	string line;
	fstream file;
	file.open(fileName);
	if (file.is_open())
	{
		getline(file, line);
		stringstream geek(line);
		int number = 0, coll = 0;
		geek >> number;
		setMatrrix(number);
		while (file.good())
		{
			for (int j = 0; j < cities; j++) {
				getline(file, line);
				int currIndex = 0, m = 0;
				for (int i = 0; i < cities; i++){
					ostringstream oss;
					while (line[m] != ' ') {
						oss << line[m];
						m++;
					}
					m++;
					istringstream iss(oss.str());
					iss >> matrix[coll][currIndex];
					currIndex++;
				}
				coll++;
			}
		}
		file.close();
	}
	else cout << "Unable to open file" << endl;
}