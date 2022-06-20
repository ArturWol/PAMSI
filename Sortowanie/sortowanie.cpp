#include "sortowanie.h"

//**************************
//
// SORTOWANIE PRZEZ SCALANIE
//
//**************************

void scal(int *tab, int *pom, int lewy, int srodek, int prawy)
{

    int i = lewy, j = srodek + 1;

    // kopiujemy lewą i prawą część tablicy do tablicy pomocniczej
    for (int i = lewy; i <= prawy; i++)
        pom[i] = tab[i];

    // scalenie dwóch podtablic pomocniczych i zapisanie ich
    // we własciwej tablicy
    for (int k = lewy; k <= prawy; k++)
        if (i <= srodek)
            if (j <= prawy)
                if (pom[j] < pom[i])
                    tab[k] = pom[j++];
                else
                    tab[k] = pom[i++];
            else
                tab[k] = pom[i++];
        else
            tab[k] = pom[j++];
}

void sort_scal(int *tab, int *pom, int lewy, int prawy)
{
    // gdy mamy jeden element, to jest on już posortowany
    if (prawy <= lewy)
        return;

    // znajdujemy srodek podtablicy
    int srodek = (prawy + lewy) / 2;

    // dzielimy tablice na częsć lewą i prawa
    sort_scal(tab, pom, lewy, srodek);
    sort_scal(tab, pom, srodek + 1, prawy);

    // scalamy dwie już posortowane tablice
    scal(tab, pom, lewy, srodek, prawy);
}

//******************
//
// SORTOWANIE SZYBKIE
//
//******************

void quick_sort(int *tab, int lewy, int prawy)
{
    if (prawy <= lewy)
        return;

    int i = lewy - 1, j = prawy + 1,
        pivot = tab[(lewy + prawy) / 2]; // wybieramy punkt odniesienia

    while (1)
    {
        // szukam elementu wiekszego lub rownego piwot stojacego
        // po prawej stronie wartosci pivot
        while (pivot > tab[++i])
            ;

        // szukam elementu mniejszego lub rownego pivot stojacego
        // po lewej stronie wartosci pivot
        while (pivot < tab[--j])
            ;

        // jesli liczniki sie nie minely to zamień elementy ze soba
        // stojace po niewlasciwej stronie elementu pivot
        if (i <= j)
            // funkcja swap zamienia wartosciami tab[i] z tab[j]
            swap(tab[i], tab[j]);
        else
            break;
    }

    if (j > lewy)
        quick_sort(tab, lewy, j);
    if (i < prawy)
        quick_sort(tab, i, prawy);
}

//*************************
//
// SORTOWANIE INTROSPEKTYWNE
//
//*************************

void insertionsort(int *tab, int lewy, int prawy)
{
    for (int i = lewy + 1; i <= prawy; i++)
    {
        int key = tab[i];
        int j = i;

        while (j > lewy && tab[j - 1] > key)
        {
            tab[j] = tab[j - 1];
            j--;
        }
        tab[j] = key;
    }
}

//*********
//
// SORRTOWANIE PRZEZ KOPCOWANIE
//
// ********

void heapsort(int *lewy, int *prawy)
{
    make_heap(lewy, prawy);
    sort_heap(lewy, prawy);
}

// funkcja potrzebna do introsort
int partition(int *tab, int lewy, int prawy)
{
    int pivot = tab[(lewy + prawy) / 2], i = lewy, j = prawy; // pivot zawsze jest na środku

    while (true)
    {
        while (tab[j] > pivot)
            j--;

        while (tab[i] < pivot)
            i++;

        if (i < j)
            swap(tab[i++], tab[j--]);
        else
            return j;
    }
}

//**********
//
// INTRO SORT
//
//**********

void introsort(int *tab, int *lewy, int *prawy, int maxdepth)
{
    if ((prawy - lewy) < 16)
        insertionsort(tab, lewy - tab, prawy - tab);
    else if (maxdepth == 0)
        heapsort(lewy, prawy + 1);
    else
    {
        int pivot = partition(tab, lewy - tab, prawy - tab);
        introsort(tab, lewy, tab + pivot, maxdepth - 1);
        introsort(tab, tab + pivot + 1, prawy, maxdepth - 1);
    }
}

void wypelnij_rand(int **tab, int n)
{

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tab[i][j] = rand() % 100000 + 1;
        }
    }
}

void sort_procent(int *tab, int n, double procent)
{
    if (procent == 100) // kiedy cala tablica posortowana
    {
        sort(tab, tab + n, greater<int>());
        return;
    }
    sort(tab, tab + (int)((n * procent) / 100));
}

void sprawdz_posortowane(int **tab, int n)
{
    for (int i; i < 100; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (tab[j] > tab[j + 1])
            {
                cout << "tablica nie posortowana! \n Zamykam program...";
                cin.get();
                exit(1);
            }
        }
    }
}

void sprawdz_czy_otwarty(ofstream &file)
{
    if (!file.is_open())
    {
        cout << "Plik nie otwarty! \n Zamykam program...";
        cin.get();
        exit(1);
    }
}

int main()
{

    ofstream plik("Wyniki.txt");
    sprawdz_czy_otwarty(plik);

    int n, a, *pom, w = 100;
    double procent;
    int **tab100, **tab101, **tab102;

    cout << "Podaj liczbe komorek: ";
    cin >> n;

    tab100 = new int *[w]; // przydzielenie pamięci na w wierszy
    tab101 = new int *[w];
    tab102 = new int *[w];

    for (int i = 0; i < w; i++)
    {
        tab100[i] = new int[n]; // przydzielenie dla każdego wiersza po n komórek
        tab101[i] = new int[n];
        tab102[i] = new int[n];
    }

    pom = new int[n]; // przydzielenie pamięci na tablicę pomocniczą

    int maxdepth = log(n) * 2;

    wypelnij_rand(tab100, n); // wypełnienie tablicy losowymi liczbami

    cout << "Podaj procent posortowanej tablicy: " << endl;
    cout << "0%, 25%, 50%, 75%, 95%, 99%, 99,7%, 100% " << endl;
    cout << "(Jesli '100%' wtedy posortowana w odwrotnej kolejnosci)" << endl;
    cin >> procent;

    for (int i = 0; i < w; i++)
    {
        sort_procent(tab100[i], n, procent);
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tab101[i][j] = tab100[i][j];
        }
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tab102[i][j] = tab100[i][j];
        }
    }

    // sortowanie wczytanej tablicy
    cout << "Wybierz rodzaj sortowania \n";
    cout << "1: sortowanie przez scalanie \n";
    cout << "2: sortowanie szybkie \n";
    cout << "3: sortowanie introspektywne \n";
    cout << "4: porownanie czasow pracy algorytmow \n";

    cin >> a;

    switch (a)
    {
    case 1:
    {
        for (int i; i < w; i++)
        {
            sort_scal(tab100[i], pom, 0, n - 1);
        }
        sprawdz_posortowane(tab100, n);
    }
    break;
    case 2:
    {
        for (int i; i < w; i++)
        {
            quick_sort(tab100[i], 0, n - 1);
        }
        sprawdz_posortowane(tab100, n);
    }
    break;
    case 3:
    {
        for (int i; i < w; i++)
        {
            introsort(tab100[i], tab100[i], tab100[i] + n - 1, maxdepth);
        }
        sprawdz_posortowane(tab100, n);
    }
    break;
    case 4:
    {
        auto t_start = chrono::high_resolution_clock::now();
        for (int i; i < w; i++)
        {
            sort_scal(tab100[i], pom, 0, n - 1);
        }
        auto t_end = chrono::high_resolution_clock::now();
        sprawdz_posortowane(tab100, n);
        cout << "Sortowanie przez scalanie..." << endl;
        plik << "sortowanie przez scalalnie" << endl;
        plik << chrono::duration<double, milli>(t_end - t_start).count();
        plik << endl;

        auto t_start1 = chrono::high_resolution_clock::now();
        for (int i; i < w; i++)
        {
            quick_sort(tab101[i], 0, n - 1);
        }
        auto t_end1 = chrono::high_resolution_clock::now();
        sprawdz_posortowane(tab101, n);
        cout << "Sortowanie szybkie..." << endl;
        plik << "sortowanie szybkie" << endl;
        plik << chrono::duration<double, milli>(t_end1 - t_start1).count();
        plik << endl;

        auto t_start2 = chrono::high_resolution_clock::now();
        for (int i; i < w; i++)
        {
            introsort(tab102[i], tab102[i], tab102[i] + n - 1, maxdepth);
        }
        auto t_end2 = chrono::high_resolution_clock::now();
        sprawdz_posortowane(tab102, n);
        cout << "Sortowanie introspektywne..." << endl;
        plik << "sortowanie introspektywne" << endl;
        plik << chrono::duration<double, milli>(t_end2 - t_start2).count();
        plik << endl;
    }
    break;
    }

    cin.get();
    plik.close();
    return 0;
}