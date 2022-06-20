#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;

void sort_scal(int *tab,int *pom, int lewy, int prawy);
void quick_sort(int *tab, int lewy, int prawy);
void introsort(int *tab, int *left, int *right, int maxdepth);