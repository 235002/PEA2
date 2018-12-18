#include "pch.h"
#include "BruteForce.h"
#include "Library.cpp"
using namespace std;

BruteForce::BruteForce()
{
	v0 = 0;
}

BruteForce::~BruteForce()
{
}

//Funkcja rozwi¹zuj¹ca problem komiwoja¿era metod¹ Brute Force (przegl¹d zupe³ny)
//c - liczba miast, &t referenencja do macierzy odleg³oœci
void BruteForce::algorytm(int start, Matrix macierz) {
	n = macierz.getCities();				//Przypisanie liczby miast
	Sh[shptr++] = start;					//Przypisanie wierzcho³ka startowego do pozycji o 1 wiêkszej od shptr

	if (shptr < n)
	{
		visited[start] = true;				//Ustwaienie true dla wierzcho³ka pocz¹tkowego odwiedzonego
		for (int u = 0; u < n; u++)
			if ((macierz.matrix[start][u] != 0) && !visited[u])//Je¿eli dla miasta statowego i miasta iterowanego koszt jest ró¿ny od zera oraz miasto jest nie odwiedzone
			{
				try												//Próbujemy zwiêkszyæ koszt œcie¿ki
				{												//Wywo³ujemy rekurencynie funkcjê jeszcze raz dla aktualnego wierzcho³ka
					dh += macierz.matrix[start][u];				//Odejmujemy koszt je¿eli w danym wierzcholku ju¿ byliœmy
					algorytm(u, macierz);
					dh -= macierz.matrix[start][u];
				}
				catch (exception e)
				{
					cout << "Wyst¹pi³ b³¹d!" << endl;
				}
			}
		visited[start] = false;
	}
	else if (macierz.matrix[v0][start] != 0)
	{
		dh += macierz.matrix[start][v0];		//Dodajemy koszt do ca³kowitego kosztu
		if (dh < d)								//Jeœli uzyskany koszt jest mniejszy od poprzedniego
		{										//Przypisujemy mnieszy koszt
			d = dh;								//Przypisujemy œcie¿kê w pêtli
			for (int u = 0; u < shptr; u++)
				S[u] = Sh[u];
			sptr = shptr;
		}
		dh -= macierz.matrix[start][v0];
	}
	shptr--;
}

void BruteForce::przegladZupelny(Matrix matrix, int v0) {
	n = matrix.getCities();					//Pobieramy informacje o liczbie miast i tworzymy nowe tablice
	S = new int[n];
	Sh = new int[n];
	visited = new bool[matrix.getCities()];


	for (int i = 0; i < matrix.getCities(); i++)//Oznaczenie wszystkich miast jako nieodwiedzonych
	{
		visited[i] = false;
	}
	sptr = shptr = 0;							//Przypisanie wartoœci do zmiennych ustawienie kosztu œcie¿ki na wartoœæ maksymaln¹
	d = maxINT;
	dh = 0;

	algorytm(v0, matrix);						//Wywo³anie alorytmu przegl¹du zupe³nego dla wierzcho³ka v0 i macierzy matrix

	cout << endl;
	cout << "Najkrotsza sciezka po wierzcholkach: ";//Wypisanie wyników
	if (sptr)
	{
		for (int i = 0; i < sptr; i++)
		{
			cout << S[i] << " ";
		}
		cout << v0 << endl;
		cout << "Koszt sciezki: " << d << endl;
	}
	else cout << "Brak cyklu Hamiltonowskiego" << endl;

	delete[] S;											//Zwolnienie pamiêci
	delete[] Sh;
	delete[] visited;
}