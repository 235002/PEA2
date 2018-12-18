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

//Funkcja rozwi�zuj�ca problem komiwoja�era metod� Brute Force (przegl�d zupe�ny)
//c - liczba miast, &t referenencja do macierzy odleg�o�ci
void BruteForce::algorytm(int start, Matrix macierz) {
	n = macierz.getCities();				//Przypisanie liczby miast
	Sh[shptr++] = start;					//Przypisanie wierzcho�ka startowego do pozycji o 1 wi�kszej od shptr

	if (shptr < n)
	{
		visited[start] = true;				//Ustwaienie true dla wierzcho�ka pocz�tkowego odwiedzonego
		for (int u = 0; u < n; u++)
			if ((macierz.matrix[start][u] != 0) && !visited[u])//Je�eli dla miasta statowego i miasta iterowanego koszt jest r�ny od zera oraz miasto jest nie odwiedzone
			{
				try												//Pr�bujemy zwi�kszy� koszt �cie�ki
				{												//Wywo�ujemy rekurencynie funkcj� jeszcze raz dla aktualnego wierzcho�ka
					dh += macierz.matrix[start][u];				//Odejmujemy koszt je�eli w danym wierzcholku ju� byli�my
					algorytm(u, macierz);
					dh -= macierz.matrix[start][u];
				}
				catch (exception e)
				{
					cout << "Wyst�pi� b��d!" << endl;
				}
			}
		visited[start] = false;
	}
	else if (macierz.matrix[v0][start] != 0)
	{
		dh += macierz.matrix[start][v0];		//Dodajemy koszt do ca�kowitego kosztu
		if (dh < d)								//Je�li uzyskany koszt jest mniejszy od poprzedniego
		{										//Przypisujemy mnieszy koszt
			d = dh;								//Przypisujemy �cie�k� w p�tli
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
	sptr = shptr = 0;							//Przypisanie warto�ci do zmiennych ustawienie kosztu �cie�ki na warto�� maksymaln�
	d = maxINT;
	dh = 0;

	algorytm(v0, matrix);						//Wywo�anie alorytmu przegl�du zupe�nego dla wierzcho�ka v0 i macierzy matrix

	cout << endl;
	cout << "Najkrotsza sciezka po wierzcholkach: ";//Wypisanie wynik�w
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

	delete[] S;											//Zwolnienie pami�ci
	delete[] Sh;
	delete[] visited;
}