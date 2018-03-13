// Projekt.cpp : Defines the entry point for the console application.
// Projek è.6 - SelectSort . Šimoník Dominik

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int porovnani;
int vymena;

/**
Tøídící algoritmus SelectSort, 
@param a pole/vector který chceme tímto aloritmem setøídit
@param N poèet prvkù pole/vectoru, v našem pøípadì je to také øád permutace
*/
void SelectSort (vector<int> a, const int N) {
	porovnani = 0;
	vymena = 0;
	for (int i = 0; i < N; i++) {
		int min = i;
		for (int j = i + 1; j < N; j++) {
			porovnani = porovnani + 1;
			if (a[j] < a[min]) {
				min = j;
			}
		}
		if (i != min) {
			exchange (a[min], a[i]);
			vymena = vymena + 2;
		}
	}
}

/**
Funkce, která pøevezme statistické data o tøídìní a vytvoøí výstupní csv soubor
@param porovnani vector se statistickými údaji o poètu porovnání v tøídícím algoritmu
@param vymena vector se statistickými údaji o poètu výmìn v tøídícím algoritmu
@param delkaPorovnani nejvyšší hodnota poètu porovnání
@param delkaPorovnani nejvyšší hodnota poètu výmìn
*/
void vystupDoTabulek (vector<int> porovnani, vector<int> vymena, int delkaPorovnani, int delkaVymena) {
	ofstream vystup ("tabulkaCetnosti.csv");
	vystup << "Poèet" << ";Èetnost" << endl;
	vystup << "Porovnání" << endl;
	for (int i = 0; i <= delkaPorovnani; i++) {
		if (porovnani.at (i) > 0) {
			vystup << i << ";" << porovnani.at (i) << endl;
		}
	}
	vystup << "Výmìna" << endl;
	for (int i = 0; i <= delkaVymena; i++) {
		if (vymena.at (i) > 0) {
			vystup << i << ";" << vymena.at (i) << endl;
		}
	}
}


int main()
{
	unsigned int radPermutace; /**< radPermutace integer s hodnotou øádu permutace */
	unsigned int tempPocet; /**< tempPocet pomocný integer s hodnotou pøedchozíhp poètu porovnani  */
	unsigned int tempVymena; /**< tempVymena pomocný integer s hodnotou pøedchozího poètu výmìn */
	unsigned int delkaPorovnani = 0;/**< delkaPorovnani maximální poèet porovnání */
	unsigned int delkaVymena = 0; /**< delkaVymena maximální poèet výmìn */
	vector<int> trideni; /**< trideni vector sloužící k permutacím */
	vector<int> porovnaniPocet; /**< porovnaniPocet vector k ukládání dat o poètu porovnání */
	vector<int> vymenaPocet; /**< vymenaPocet vector k ukládání poètu výmìn */

	cout << "Zadejte rad permutace, ktery chcete testovat: ";
	cin >> radPermutace;
	trideni.resize (radPermutace);
	for (int i = 0; i < radPermutace; i++) {
		trideni[i] = i + 1;
	}
	porovnaniPocet.resize (1);
	vymenaPocet.resize (1);
	cout << "Zacalo trideni Vsech permutaci" << endl;
	do {
		vector<int> keTrideni (trideni);
		SelectSort (keTrideni,radPermutace);
		tempPocet = 0;
		tempVymena = 0;
		if (porovnani > delkaPorovnani) {
			delkaPorovnani = porovnani;
			porovnaniPocet.resize (delkaPorovnani+1);
		}
		/** 
		resize + 1 je z dùvodu toho, že se nedržím úplnì indexù, pokud byl napøíklad poèet výmìn 6
		,tak je to na indexu è.7 z dùvodu toho, že používám index 1 pro ukládání 0-vých výmìn
		*/
		if (vymena > delkaVymena) {
			delkaVymena = vymena;
			vymenaPocet.resize (delkaVymena+1);
		}
		tempPocet = porovnaniPocet.at (porovnani);
		porovnaniPocet[porovnani] = tempPocet + 1;
		tempVymena = vymenaPocet.at (vymena);
		vymenaPocet[vymena] = tempVymena + 1;
	} while (next_permutation (trideni.begin(), trideni.end()));
	vystupDoTabulek (porovnaniPocet, vymenaPocet, delkaPorovnani, delkaVymena);
	cout << "Trideni bylo ukonceno, vystup najdete v souboru tabulkaCetnosti.csv" << endl;
	return 0;
}

