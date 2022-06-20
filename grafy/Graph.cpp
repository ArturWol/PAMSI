#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;


//TWORZENIE GRAFU
Graph::Graph(int Wierzcholki, int Krawedzie, int Start)
{
	this->Wierzcholki = Wierzcholki;
	this->Krawedzie = Krawedzie;
	this->Start = Start;
	MacierzGrafu = new int*[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++) {
		MacierzGrafu[i] = new int[Wierzcholki];
	}
	for (int i = 0; i < Wierzcholki; i++)
		for (int j = 0; j < Wierzcholki; j++)
			MacierzGrafu[i][j] = 0;

	Lista = new Element*[Wierzcholki];

	for (int i = 0; i < Wierzcholki; i++)
		Lista[i] = NULL;



}




int Graph::Minimum(dane* tab) {
	int min = -1;
	int mindist = INT_MAX;
	for (int i = 0; i < Wierzcholki; i++) {
		if (!tab[i].odwiedzony && tab[i].dystans < mindist) {
			min = i;
			mindist = tab[i].dystans;
		}
	}
	return min;
}
//ALGORYTM DIJKSTRA DLA REPREZENTACJI GRAFU LISTY SASIEDZTWA
dane* Graph::Dijkstra_Lista() {

	dane* tab = new dane[Wierzcholki];
	droga = new int[Wierzcholki];
	Element *pomocniczy;
	for (int i = 0; i < Wierzcholki; i++) {
		if (i == Start)
		{
			tab[i].dystans = 0;
		}
		else
		{
			tab[i].dystans = INT_MAX;
		}
		tab[i].odwiedzony = false;
		droga[i] = -1;
	}

	int min = Minimum(tab);

	while (min != -1) {
		tab[min].odwiedzony = true;
		pomocniczy = Lista[min];

		for (pomocniczy = Lista[min]; pomocniczy; pomocniczy = pomocniczy->nastepny)
		{
			if (tab[min].dystans + pomocniczy->waga < tab[pomocniczy->wezel].dystans) {
				tab[pomocniczy->wezel].dystans = tab[min].dystans + pomocniczy->waga;
				droga[pomocniczy->wezel] = min;
			}

		}
		min = Minimum(tab);

	}
	return tab;
}


//ALGORYTM DIJKSTRA DLA REPREZENTACJI GRAFU MACIERZY SASIEDZTWA
dane* Graph::Dijkstra() {

	dane* tab = new dane[Wierzcholki];
	droga = new int[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++) {
		if (i == Start)
		{
			tab[i].dystans = 0;
		}
		else
		{
			tab[i].dystans = INT_MAX;
		}
		tab[i].odwiedzony = false;
		droga[i] = -1;
	}

	int min = Minimum(tab);
	while (min != -1) {
		tab[min].odwiedzony = true;
		for (int i = 0; i < Wierzcholki; i++) {
			if (MacierzGrafu[min][i] > 0 && tab[min].dystans + MacierzGrafu[min][i] < tab[i].dystans) {
				tab[i].dystans = tab[min].dystans + MacierzGrafu[min][i];
				droga[i] = min;
			}
		}
		min = Minimum(tab);
	}

	return tab;
}

//FUNKCJA DODAJACA KRAWEDZIE
int Graph::dodaj_krawedz(int i, int j, int waga)
{

	element = new Element;
	element->wezel = j;
	element->waga = waga;
	element->nastepny = Lista[i];
	Lista[i] = element;

	return MacierzGrafu[i][j] = waga;



}

//FUNKCJA ODPOWIADAJACA ZA WYSWIETLENIE GRAFU - MACIERZY
void Graph::wyswietl()
{
	for (int i = 0; i < Wierzcholki; i++)
	{
		for (int j = 0; j < Wierzcholki; j++)
		{
			std::cout << MacierzGrafu[i][j] << "\t";
		}
		std::cout << endl;
	}
}

//FUNKCJA ODPOWIADAJACA ZA WYSWIETLENIE GRAFU - LISTY
void Graph::wyswietl_liste()
{
	Element *tmp;
	for (int i = 0; i < Wierzcholki; i++)
	{
		tmp = Lista[i];
		cout << i << ":";
		while (tmp)
		{
			cout << tmp->wezel << " waga :" << tmp->waga<<" ";
			tmp = tmp->nastepny;
		}
		cout << endl;
	}
}

//ZAPISYWANIE GRAFU DO PLIKU
void Graph::zapisz( dane *tab) {
	int licznik = 0;
	int *Tab_drogi = new int[Wierzcholki];
	ofstream plik;
	plik.open("Graf.txt");
	for (int i = 0; i < Wierzcholki; i++)
	{
		plik << i << ":" ;
		for (int j = i; j > -1; j = droga[j])
			Tab_drogi[licznik++] = j;
		while (licznik)
		plik << Tab_drogi[--licznik] << "->";
		plik << "( "<< tab[i].dystans << ") " << endl;
	}
	plik.close();
}


Graph::~Graph()
{
}

