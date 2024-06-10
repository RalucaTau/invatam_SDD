#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARINING
#pragma warning(disable:4996)

typedef struct {
	int prioritate;
	char* denumire;
	float pret;
}Produs;

typedef struct {
	int nrElemente;
	Produs* vect;
}heap;


void filtrare(heap h, int index) {
	int radIndex = index;
	int StIndex = radIndex * 2 + 1;
	int DrIndex = radIndex * 2 + 2;

	if (StIndex < h.nrElemente && h.vect[StIndex].prioritate < h.vect[radIndex].prioritate) {
		radIndex = StIndex;
	}
	if (DrIndex < h.nrElemente && h.vect[DrIndex].prioritate < h.vect[radIndex].prioritate) {
		radIndex = DrIndex;
	}

	if (radIndex != index) {
		Produs temp = h.vect[radIndex];
		h.vect[radIndex] = h.vect[index];
		h.vect[index] = temp;
	}

}

heap adaugare(heap h, Produs prod) {
	Produs* vectNou = (Produs*)malloc(sizeof(Produs) * (h.nrElemente+1));
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElemente++;
	vectNou[h.nrElemente - 1] = prod;

	free(h.vect);

	h.vect = vectNou;

	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, Produs* extras) {

	Produs* vectNou = (Produs*)malloc(sizeof(Produs) * (h.nrElemente - 1));

	(*extras) = h.vect[0];

	Produs temp = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente-1];
	h.vect[h.nrElemente - 1] = temp;

	h.nrElemente--;

	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}

	free(h.vect);
	h.vect = vectNou;

	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}


void afisare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		printf("Prioritate = %d, Denumire = %s, Pret = %5.2f\n",
			h.vect[i].prioritate, h.vect[i].denumire, h.vect[i].pret);
	}
}

void main() {
	heap h;
	char buffer[40];
	FILE* f = fopen("fisierHeap.txt", "r");
	fscanf(f, "%d", &h.nrElemente);

	h.vect = (Produs*)malloc(sizeof(Produs) * h.nrElemente);

	for (int i = 0; i < h.nrElemente; i++) {
		fscanf(f, "%d", &h.vect[i].prioritate);

		fscanf(f,"%s", buffer);
		h.vect[i].denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(h.vect[i].denumire, buffer);

		fscanf(f,"%f", &h.vect[i].pret);

	}
	fclose(f);


	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisare(h);


	Produs nou;
	printf("\nPrioritate: ");
	scanf("%d", &nou.prioritate);
	printf("\nDenumire: ");
	scanf( "%s", buffer);
	nou.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(nou.denumire, buffer);

	printf("\nPret: ");
	scanf("%d", &nou.pret);

	h = adaugare(h, nou);
	afisare(h);

	Produs extras;
	h = extragere(h, &extras);
	printf("\n----------Dupa stergere-----------\n");
	afisare(h);

	int nr = h.nrElemente;

	Produs* vectNou = (Produs*)malloc(sizeof(Produs) * (h.nrElemente));
	for (int i = 0; i < nr; i++) {
		h = extragere(h, &extras);
		vectNou[i] = extras;
	}

	printf("\n----------Dupa ordonare-----------\n");

	for (int i = 0; i < nr; i++) {
		printf("Prioritate = %d, Denumire = %s, Pret = %5.2f\n",
			vectNou[i].prioritate, vectNou[i].denumire, vectNou[i].pret);
	}


}