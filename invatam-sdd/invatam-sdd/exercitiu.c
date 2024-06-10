//ABC + lista dubla
#define _CRT_SECURE_NO_WARNING
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct {
	int prioritate;
	char* denumire;
	int nrCredite;
}Curs;

typedef struct {
	Curs* vect;
	int nrElem;
}heap;


void filtrare(heap h, int index) {
	int rad = index;
	int radStanga = index * 2 + 1;
	int radDreapta = index * 2 + 2;

	if (radStanga<h.nrElem && h.vect[radStanga].prioritate>h.vect[rad].prioritate) {
		rad = radStanga;
	}
	if (radDreapta<h.nrElem && h.vect[radDreapta].prioritate>h.vect[rad].prioritate) {
		rad = radDreapta;
	}

	if (rad != index) {
		Curs c = h.vect[index];
		h.vect[index] = h.vect[rad];
		h.vect[rad] = c;
	}
}




void parcurgere(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("index: %d. Prioritate = %d, Denumire = %s\n",
			i, h.vect[i].prioritate, h.vect[i].denumire);
	}
}




void main() {
	FILE* f = fopen("FisierAVL.txt", "r");
	

	char separatori[] = ";\n";
	char linie[50];

	heap h;
	fgets(linie, sizeof(linie), f);
	char* element = strtok(linie, separatori);
	h.nrElem = (int)atoi(element);

	h.vect = (Curs*)malloc(sizeof(Curs)*h.nrElem);
	int i = 0;

	while (fgets(linie, sizeof(linie), f)) {
		char* element = NULL;

		element = strtok(linie, separatori);
		h.vect[i].prioritate = (int)atoi(element);

		element = strtok(NULL, separatori);
		h.vect[i].denumire = (char*)malloc(sizeof(char) * (1 + strlen(element)));
		strcpy(h.vect[i].denumire, element);

		element= strtok(NULL, separatori);
		h.vect[i].nrCredite = (int)atoi(element);

		i++;
	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	parcurgere(h);
}