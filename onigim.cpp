#include <iostream>
#include <fstream>
#define MAX_ELEVI 1000
#define MAX_PUNCTAJ 300
using namespace std;
// structuri de date abstracte
struct Elev
{
	int id;
	Elev *urmatorul;
};
struct ListaElevi
{
	int nrElevi;
	Elev *primul, *ultimul;
};
// variabile globale
ListaElevi L[MAX_ELEVI+1];
int nrElevi, nrPunctajeDistincte;
int punctajDistinct[MAX_ELEVI], punctajElev[MAX_ELEVI];
int aparitiiPunctaj[MAX_PUNCTAJ+1];
// functii ajutatoare
void initializeazaLista(ListaElevi & L);
void adaugaInLista(ListaElevi & L, int id);
void calculeazaPunctajeleElevilor();
// functia principala
int main()
{
	int i;
	ifstream fin("onigim.in");
	fin >> nrElevi >> nrPunctajeDistincte;
	for (i = 0; i < nrPunctajeDistincte; i++)
	{
		fin >> punctajDistinct[i];
		initializeazaLista(L[i]);
	}
	initializeazaLista(L[nrPunctajeDistincte]);
	for (i = 0; i < nrElevi; i++)
	{
		int nrEleviCuPunctajMaiMicDecatElevulI;
		fin >> nrEleviCuPunctajMaiMicDecatElevulI;
		adaugaInLista(L[nrEleviCuPunctajMaiMicDecatElevulI], i);
	}
	fin.close();
	calculeazaPunctajeleElevilor();
	ofstream fout("onigim.out");
	for (i = 0; i < nrElevi; i++)
		fout << punctajElev[i] << ' ';
	int nrDistinctii = 0;
	for (i = nrPunctajeDistincte-3; i < nrPunctajeDistincte; i++)
		nrDistinctii += aparitiiPunctaj[punctajDistinct[i]];
	fout << '\n' << nrDistinctii;
	int nrMaxEleviCuAcelasiPunctaj = 0;
	for (i = 0; i <= MAX_PUNCTAJ; i++)
		if (aparitiiPunctaj[i] > nrMaxEleviCuAcelasiPunctaj)
			nrMaxEleviCuAcelasiPunctaj = aparitiiPunctaj[i];
	fout << '\n' << nrMaxEleviCuAcelasiPunctaj;	
	fout.close();
	return 0;
}
void calculeazaPunctajeleElevilor()
{
	for (int i = 0, j = 0; i < nrPunctajeDistincte && j <= nrPunctajeDistincte; i++)
		if (L[j].nrElevi > 0)
		{
			for (Elev *e = L[j].primul; e; e = e->urmatorul)
			{
				int punctaj = punctajDistinct[i];
				punctajElev[e->id] = punctaj;
				aparitiiPunctaj[punctaj]++;
			}
			j += L[j].nrElevi;
		}
}
void initializeazaLista(ListaElevi & L)
{
	L.nrElevi = 0;
	L.primul = L.ultimul = 0;
}
void adaugaInLista(ListaElevi & L, int id)
{
	Elev *noulElev = new Elev;
	noulElev->id = id;
	noulElev->urmatorul = 0;
	if (!L.primul)
		L.primul = L.ultimul = noulElev;
	else
	{
		L.ultimul->urmatorul = noulElev;
		L.ultimul = noulElev;
	}
	L.nrElevi++;
}
