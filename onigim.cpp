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
int nrElevi, nrPunctajeDistincte, nrDistinctiiAcordate, nrMaxEleviCuAcelasiPunctaj;
int punctajDistinct[MAX_ELEVI], punctajElev[MAX_ELEVI], aparitiiPunctaj[MAX_PUNCTAJ+1];
// functii ajutatoare
void citesteDateleDeIntrare();
void calculeazaPunctajulObtinutDeFiecareElev();
void calculeazaNumarulDeDistinctiiAcordateDeOrganizatori();
void calculeazaNumarulMaximDeEleviCareAuObtinutAcelasiPunctaj();
void afiseazaDateleDeIesire();
// functia principala
int main()
{
	citesteDateleDeIntrare();
	calculeazaPunctajulObtinutDeFiecareElev();
	calculeazaNumarulDeDistinctiiAcordateDeOrganizatori();
	calculeazaNumarulMaximDeEleviCareAuObtinutAcelasiPunctaj();
	afiseazaDateleDeIesire();
	return 0;
}
void afiseazaDateleDeIesire()
{
    ofstream fout("onigim.out");
    for (int i = 0; i < nrElevi; i++)
		fout << punctajElev[i] << ' ';
    fout << '\n' << nrDistinctiiAcordate;
    fout << '\n' << nrMaxEleviCuAcelasiPunctaj;
    fout.close();
}
void calculeazaNumarulMaximDeEleviCareAuObtinutAcelasiPunctaj()
{
    for (int i = 0; i <= MAX_PUNCTAJ; i++)
		if (aparitiiPunctaj[i] > nrMaxEleviCuAcelasiPunctaj)
			nrMaxEleviCuAcelasiPunctaj = aparitiiPunctaj[i];
}
void calculeazaNumarulDeDistinctiiAcordateDeOrganizatori()
{
    int i;
    if (nrPunctajeDistincte >= 3)
        i = nrPunctajeDistincte-3;
    else
        i = 0;
    while (i < nrPunctajeDistincte)
    {
        nrDistinctiiAcordate += aparitiiPunctaj[punctajDistinct[i]];
        i++;
    }
}
void calculeazaPunctajulObtinutDeFiecareElev()
{
    for (int i = 0, j = 0;
         i < nrPunctajeDistincte && j < nrElevi; i++)
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
void initializeazaLista(ListaElevi & L)
{
	L.nrElevi = 0;
	L.primul = L.ultimul = 0;
}
void citesteDateleDeIntrare()
{
    int i;
    ifstream fin("onigim.in");
	fin >> nrElevi >> nrPunctajeDistincte;
	for (i = 0; i < nrElevi; i++)
        initializeazaLista(L[i]);
	for (i = 0; i < nrPunctajeDistincte; i++)
		fin >> punctajDistinct[i];
	for (i = 0; i < nrElevi; i++)
	{
		int nrEleviCuPunctajMaiMicDecatElevulI;
		fin >> nrEleviCuPunctajMaiMicDecatElevulI;
		adaugaInLista(L[nrEleviCuPunctajMaiMicDecatElevulI], i);
	}
	fin.close();
}
