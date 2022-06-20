
#pragma once
#include "Structure.h"

using namespace std;

//KLASA GRAFU ZAWIERA OBIEKTY I METODY POTRZEBNE DO STWORZENIA GRAFU I DZIALANIA ALGORYTMU DIJKSTRA
class Graph
{

private:

	int *droga;
	int **MacierzGrafu;
	Element *element;
	Element **Lista;
	int Wierzcholki;
	int Krawedzie;
	int Start;
public:
	Graph() {};
	Graph(int Wierzcholki , int Krawedzie, int Start);
	~Graph();
	int dodaj_krawedz(int i, int j, int waga);
	void wyswietl();
	void wyswietl_liste();
	int Minimum(dane* tab);
	dane* Dijkstra();
	dane* Dijkstra_Lista();
	void zapisz( dane *tab);


};




