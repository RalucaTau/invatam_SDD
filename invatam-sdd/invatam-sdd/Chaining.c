#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNING
#pragma warning(disable:4996)

typedef struct {
	int cod;
	char* denumire;
}produs;

typedef struct {
	produs inf;
	struct nodls* next;
}nodls;

typedef struct {
	struct nodls** vect;
	int nrElem;
}hashT;

int functieDispersie(hashT tabela, int cheie) {
	return cheie % tabela.nrElem;
}

int functieDispersie2(hashT tabela, char den[20]) {
	return den[0] % tabela.nrElem;
}

void inserareTabela(hashT tabela, produs p) {
	if (tabela.vect != NULL) {

		int pozitie = functieDispersie2(tabela, p.denumire);
		nodls* nou = (nodls*)malloc(sizeof(nodls));
		nou->inf.cod = p.cod;
		nou->inf.denumire = (char*)malloc(sizeof(char) * (1 + strlen(p.denumire)));
		strcpy(nou->inf.denumire, p.denumire);
		nou->next = NULL;

		if (tabela.vect[pozitie] == NULL) {
			tabela.vect[pozitie] = nou;
		}
		else {
			nodls* temp = tabela.vect[pozitie];
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
}

void traversareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		printf("Cod= %d, Denumire= %s\n", temp->inf.cod, temp->inf.denumire);
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela) {
	if (tabela.vect)
	{
		for (int i = 0; i < tabela.nrElem; i++) {
			if (tabela.vect[i] != NULL)
			{
				printf("Pozitia nr %d\n", i);
				traversareLS(tabela.vect[i]);
			}
		}
	}
}

void dezalocareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		nodls* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela) {
	if (tabela.vect)
	{
		for (int i = 0; i < tabela.nrElem; i++) {
			if (tabela.vect[i]) {
				dezalocareLS(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}


void main() {
	hashT tabela;
	tabela.nrElem = 30;
	tabela.vect = (nodls**)malloc(sizeof(nodls*) * tabela.nrElem);
	for (int i = 0; i < tabela.nrElem; i++) {
		tabela.vect[i] = NULL;
	}

	char buffer[20];
	int nr;
	produs p;

	FILE* f = fopen("text.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc(sizeof(char) * (1 + strlen(buffer)));
		strcpy(p.denumire, buffer);

		inserareTabela(tabela, p);

		free(p.denumire);
	}
	fclose(f);

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}