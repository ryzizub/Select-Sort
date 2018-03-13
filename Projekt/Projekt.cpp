// Projekt.cpp : Defines the entry point for the console application.
// Projek �.6 - SelectSort . �imon�k Dominik

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int porovnani;
int vymena;

/**
T��d�c� algoritmus SelectSort, 
@param a pole/vector kter� chceme t�mto aloritmem set��dit
@param N po�et prvk� pole/vectoru, v na�em p��pad� je to tak� ��d permutace
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
Funkce, kter� p�evezme statistick� data o t��d�n� a vytvo�� v�stupn� csv soubor
@param porovnani vector se statistick�mi �daji o po�tu porovn�n� v t��d�c�m algoritmu
@param vymena vector se statistick�mi �daji o po�tu v�m�n v t��d�c�m algoritmu
@param delkaPorovnani nejvy��� hodnota po�tu porovn�n�
@param delkaPorovnani nejvy��� hodnota po�tu v�m�n
*/
void vystupDoTabulek (vector<int> porovnani, vector<int> vymena, int delkaPorovnani, int delkaVymena) {
	ofstream vystup ("tabulkaCetnosti.csv");
	vystup << "Po�et" << ";�etnost" << endl;
	vystup << "Porovn�n�" << endl;
	for (int i = 0; i <= delkaPorovnani; i++) {
		if (porovnani.at (i) > 0) {
			vystup << i << ";" << porovnani.at (i) << endl;
		}
	}
	vystup << "V�m�na" << endl;
	for (int i = 0; i <= delkaVymena; i++) {
		if (vymena.at (i) > 0) {
			vystup << i << ";" << vymena.at (i) << endl;
		}
	}
}


int main()
{
	unsigned int radPermutace; /**< radPermutace integer s hodnotou ��du permutace */
	unsigned int tempPocet; /**< tempPocet pomocn� integer s hodnotou p�edchoz�hp po�tu porovnani  */
	unsigned int tempVymena; /**< tempVymena pomocn� integer s hodnotou p�edchoz�ho po�tu v�m�n */
	unsigned int delkaPorovnani = 0;/**< delkaPorovnani maxim�ln� po�et porovn�n� */
	unsigned int delkaVymena = 0; /**< delkaVymena maxim�ln� po�et v�m�n */
	vector<int> trideni; /**< trideni vector slou��c� k permutac�m */
	vector<int> porovnaniPocet; /**< porovnaniPocet vector k ukl�d�n� dat o po�tu porovn�n� */
	vector<int> vymenaPocet; /**< vymenaPocet vector k ukl�d�n� po�tu v�m�n */

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
		resize + 1 je z d�vodu toho, �e se nedr��m �pln� index�, pokud byl nap��klad po�et v�m�n 6
		,tak je to na indexu �.7 z d�vodu toho, �e pou��v�m index 1 pro ukl�d�n� 0-v�ch v�m�n
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

