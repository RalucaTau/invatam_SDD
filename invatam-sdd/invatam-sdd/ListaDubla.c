#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARINING
#pragma warning(disable:4996)

struct Produs {
	int numar;
	char* denumire;
	char* categorie;
};

typedef struct Produs Produs;

struct nodD {
	Produs inf;
	struct nodD* next, * prev;
};

typedef struct nodD nodD;

struct listaDubla {
	struct nodD* prim, * ultim;
};

typedef struct listaDubla listaDubla;

listaDubla inserareLD(listaDubla cap, Produs p) {

	nodD* nou = (nodD*)malloc(sizeof(nodD));
	
	nou->inf.numar = p.numar;
	nou->inf.categorie = (char*)malloc(sizeof(char) * (1 + strlen(p.categorie)));
	strcpy(nou->inf.categorie, p.categorie);
	nou->inf.denumire = (char*)malloc(sizeof(char) * (1 + strlen(p.denumire)));
	strcpy(nou->inf.denumire, p.denumire);

	nou->next = NULL;
	nou->prev = cap.ultim;

	if (cap.prim == NULL) {
		cap.prim = cap.ultim = nou;
	}
	else {
		cap.ultim->next = nou;
		cap.ultim = nou;
	}
	return cap;
}

listaDubla* stergere(listaDubla* lista, nodD* sters) {
	nodD* temp = lista->prim;

	if (lista->ultim == NULL && lista->prim == NULL) {
		return NULL;
	}

	if (lista->prim == sters && lista->ultim == sters) {
		lista->prim = NULL;
		lista->ultim = NULL;
		free(sters->inf.categorie);
		free(sters->inf.denumire);
		free(sters);

		return NULL;
	}
	else if (lista->prim == sters) {
		lista->prim = lista->prim->next;
		lista->prim->prev = NULL;
		free(sters->inf.categorie);
		free(sters->inf.denumire);
		free(sters);

		return lista;
	}
	else if (lista->ultim == sters) {
		lista->ultim = lista->ultim->prev;
		lista->ultim->next = NULL;

		free(sters->inf.categorie);
		free(sters->inf.denumire);
		free(sters);

		return lista;
	}

	nodD* urmator = sters->next;
	nodD* anterior = sters->prev;
	anterior->next = urmator;
	urmator->prev = anterior;

	free(sters->inf.categorie);
	free(sters->inf.denumire);
	free(sters);

	return lista;

}

void stergereDupaNumar(listaDubla* lista, int nr) {
	nodD* temp = lista->prim;
	while (temp) {
		if (nr == temp->inf.numar) {
			nodD* sters = temp;
			temp = temp->next;
			stergere(lista, sters);

		}
		else {
			temp = temp->next;
		}
	}
}


void traversareInversa(listaDubla lista) {
	nodD* temp = lista.ultim;
	while (temp) {
		printf("Categorie = %s, Numar = %d, Denumire = %s\n",
			temp->inf.categorie, temp->inf.numar, temp->inf.denumire);
		temp = temp->prev;
	}
}

void main() {
	FILE* f = fopen("fisierListaDeListe.txt", "r");

	listaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	char separatori[] = ",\n";
	char linie[40];

	while (fgets(linie, sizeof(linie), f)) {
		Produs p;
		char* element = NULL;

		element = strtok(linie, separatori);
		p.categorie = (char*)malloc(sizeof(char) * (1 + strlen(element)));
		strcpy(p.categorie, element);

		element = strtok(NULL, separatori);
		p.denumire = (char*)malloc(sizeof(char) * (1 + strlen(element)));
		strcpy(p.denumire, element);

		element = strtok(NULL, separatori);
		p.numar = (int)atoi(element);

		lista = inserareLD(lista, p);
	}

	fclose(f);

	traversareInversa(lista);

	stergereDupaNumar(&lista, 3);
	printf("\nSTERGERE\n");
	traversareInversa(lista);

	stergereDupaNumar(&lista, 2);
	printf("\nSTERGERE\n");
	traversareInversa(lista);

	stergereDupaNumar(&lista, 1);
	printf("\nSTERGERE\n");
	traversareInversa(lista);

	stergereDupaNumar(&lista, 4);
	printf("\nSTERGERE\n");
	traversareInversa(lista);

}