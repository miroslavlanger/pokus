// RadixSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "time.h"

using namespace std;

int GetRandom(int LOWER_BOUND, int UPPER_BOUND) {
	if (LOWER_BOUND == 0) {
		return (rand() % (UPPER_BOUND + 1));
	} else {
		return (rand() % UPPER_BOUND + LOWER_BOUND);
	};
};


//definice struktury fronta
struct TQueue {
	int value;
	TQueue *next;
 } ;


//fce prida prvek na konec fronty a vrati ukazatel na novy konec fronty
TQueue* Enqueue(TQueue* *a_head, TQueue *a_tail, int a_value) {
	TQueue *l_hlp = new TQueue; //deklarujeme pomocnou promennou a zaroven alokujeme pamet pro novy prvek fronty
	l_hlp->value = a_value; //vlozime hodnotu do nove vytvorene promenne
	l_hlp->next = NULL; // jedna se o posledni prvek fronty, bude ukazovat na NULL
	// jestlize vkladame prvni prvek, pak je a_tail NULL! Cili neexistuje zadny naslednik puvodniho konce fronty
	if (a_tail != NULL) {
		a_tail->next = l_hlp; // puvodni konec fronty ukaze na novy konec
	}
	// jeste je treba osetrit ituaci, ze fronta byla prazdna
	// ukazatel na zacatek fronty ukazuje na NULL a musi tedy ukazat na nove vlozeny prvek
	if (*a_head == NULL) {*a_head = l_hlp;};
	return l_hlp; // vratime ukazatel na novy konec fronty

};

int Dequeue(TQueue* *a_head, TQueue* *a_tail) {
	int l_val; //deklarujeme si promennou, do ktere si ulozime hodnotu cela
	TQueue *l_hlp = *a_head; //deklarujeme pomocnou promennou a zaroven ji priradime aktualni celo fronty
	*a_head = l_hlp->next; //nove celo bude prvek druhy v poradi - naslednik soucasneho cela
	l_val = l_hlp->value; // vezmeme si hodnotu z puvodniho cela fronty
	// pokud odebirame posledni prvek fronty, pak musime i koncem ukazat na NULL
	if (*a_head == NULL) {*a_tail = NULL;};
	delete l_hlp;
	return l_val;
};


int _tmain(int argc, _TCHAR* argv[])
{
	//inicializace nahodnych cisel
	srand((unsigned int)time(NULL));

	int i, x;

	// vytvorime si frontu a prihradky
	TQueue  *pHead, *pTail, *h[10], *t[10];
	// inicializace fronty a prihradek
	pHead = NULL;
	pTail = NULL;
	for (i = 0; i <=9; i++) {
		h[i] = NULL;
		t[i] = NULL;
	}

	// naplnime frontu nahodnyma hodnotama a zaroven ji vypiseme
	for (i = 1; i <=5; i++) {
		x = GetRandom(0, 1000);
		cout << x << ' ';
		pTail = Enqueue(&pHead, pTail, x);
	};

	cout << endl;

	// promenne pro rizeni cyklu a zpracovavaneho radu cisla
	bool loop = 1;
	int rad = 1, x_mod, x_div;
	while (loop) {
		// kontrola cyklu bude false
		loop = 0;
		// roztridime cisla do prihradek podle odpovidajiciho radu
		while (pHead != NULL) {
			// vezmeme prvek z cela fronty
			x = Dequeue(&pHead, &pTail);
			// zjisime cislici na pozici zkoumaneho radu
			x_div = x / rad;
			x_mod = x_div % 10;
			// zaradime cislo do prihradky
			t[x_mod] = Enqueue(&h[x_mod], t[x_mod], x);
			// zkontrolujeme, jestli mame pokracovat
			if (x_div/10) {loop = 1;};
		}
		// mame roztrideno, zretezime fronty
		for (i = 0; i <=9; i++) {
			// pokud je fronta neprazda, pak ji pridame
			if (h[i] != NULL ) {
				// pokud uz mame zacatek fronty...
				if (pHead != NULL) {
					// konec fronty ukaze na zacatek nasledujici prihradky
					pTail->next = h[i];
				} else {
					// zacatek prihradky bude zacatkem fronty
					pHead = h[i];
				}
				// konec prihradky bude novym koncem fronty
				pTail = t[i];
			}
			h[i] = NULL;
			t[i] = NULL;
		}
		// jeste navysime rad
		rad *=10;
	}


	// vypiseme serazenou frontu
	while (pHead != NULL) {
		cout << Dequeue(&pHead, &pTail) << ' ';
	}

	return 0;
}


