#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARINING
#pragma warning(disable:4996)

typedef struct {
	int numar;
	char* denumire;
	char* categorie;
}Produs;

typedef struct {
	Produs inf;
	struct nodLS* next;
}nodLS;

typedef struct {
	struct nodLS* inf;
	struct nodLS* next;
	char* categorie;
}nodLP;


void inserareLS(nodLS** cap, Produs p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->inf.numar = p.numar;
	nou->inf.categorie = (char*)malloc(sizeof(char) * (1 + strlen(p.categorie)));
	strcpy(nou->inf.categorie, p.categorie);
	nou->inf.denumire = (char*)malloc(sizeof(char) * (1 + strlen(p.denumire)));
	strcpy(nou->inf.denumire, p.denumire);
	nou->next = NULL;

	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		nodLS* temp = (*cap);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

nodLS* stergereLS(nodLS* cap, int prag) {
	if (cap == NULL) {
		return NULL;
	}

	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		if (cap->inf.numar == prag) {
			nodLS* temp = cap;
			cap = temp->next;
			free(temp->inf.categorie);
			free(temp->inf.denumire);
			free(temp);

		}
		else if (temp2 != NULL) {
			if (temp2->inf.numar == prag) {
				temp->next = temp2->next;
				free(temp2->inf.categorie);
				free(temp2->inf.denumire);
				free(temp2);
			}
		}
		temp = temp->next;
	}
}

nodLP* stergereLP(nodLP* cap, int prag) {
	nodLP* temp = cap;
	nodLP* temp2 = temp->next;
	nodLP* temp3 = NULL;

	while (temp) {
		if (temp == cap) {
			temp3 = stergereLS(temp->inf, prag);
			if (temp3 == NULL) {
				free(temp->categorie);
				free(temp->inf);
				free(temp);
				temp = temp2;
				temp->next = temp2->next;
			}
		}
		//nu e terminata, dar sunt prea stresata s o mai fac acum, ma mai uit la heap, ciao
	}
}


void inserareLP(nodLP** cap, Produs p) {
	nodLP* temp = *cap;
	nodLP* prev = NULL;

	while (temp != NULL && strcmp(temp->categorie, p.categorie) != 0) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
		nou->inf = NULL;
		nou->next = NULL;
		nou->categorie = (char*)malloc(sizeof(char) * (1 + strlen(p.categorie)));
		strcpy(nou->categorie, p.categorie);

		inserareLS(&(nou->inf), p);

		if (prev == NULL) {
			(*cap) = nou;
		}
		else {
			prev->next = nou;
		}
	}
	else {
		inserareLS(&(temp->inf), p);
	}
}


void traversareLS(nodLS* cap) {
	if (cap != NULL) {
		nodLS* temp = cap;
		while (temp) {
			printf("Categorie = %s, Numar = %d, Denumire = %s\n",
				temp->inf.categorie, temp->inf.numar, temp->inf.denumire);
			temp = temp->next;
		}
	}
}

void traversareLP(nodLP* cap) {

	nodLP* temp = cap;
	while (temp) {
		printf("\nSublista %s\n", temp->categorie);
		traversareLS(temp->inf);
		temp = temp->next;
	}
}

void main() {
	FILE* f = fopen("fisierListaDeListe.txt", "r");

	nodLP* capLP = NULL;

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

		inserareLP(&capLP, p);
	}
	fclose(f);

	traversareLP(capLP);
}