#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNING
#pragma warning(disable: 4996)

typedef struct {
	int codCurs;
	char* denumire;
	int nrCredite;
}Curs;

typedef struct {
	Curs** vect;
	int nrElem;
}hashT;

int functieDispersie(hashT tabela, int cod) {
	return cod % tabela.nrElem;
}

void inserareTabela(hashT tabela, Curs* c) {
	if (tabela.vect != NULL) {
		int pozitie = functieDispersie(tabela, c->codCurs);
		if (tabela.vect[pozitie] == NULL) {
			tabela.vect[pozitie] = c;
		}
		else {
			int index = 1;
			while (index + pozitie < tabela.nrElem) {
				if (tabela.vect[index + pozitie] == NULL) {
					tabela.vect[index + pozitie] = c;
					break;
				}
				else {
					index++;
				}
			}
		}
	}
}


void traversare(hashT t) {
	if (t.vect != NULL) {
		for (int i = 0; i < t.nrElem; i++) {
			if (t.vect[i]) {
				printf("Pozitia %d\n", i);
				printf("Cod curs = %d, denumire = %s, numar credite = %d\n",
					t.vect[i]->codCurs, t.vect[i]->denumire, t.vect[i]->nrCredite);
			}
		}
	}
}

void main() {
	FILE* f = fopen("fisierHashT.txt", "r");

	char separatori[] = ";\n";
	char linie[50];

	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (Curs**)malloc(sizeof(Curs*) * tabela.nrElem);
	for (int i = 0; i < tabela.nrElem; i++) {
		tabela.vect[i] = NULL;
	}

	while (fgets(linie, sizeof(linie), f)) {
		Curs* c = (Curs*)malloc(sizeof(Curs));
		char* element = NULL;

		element = strtok(linie, separatori);
		c->codCurs = (int)atoi(element);

		element = strtok(NULL, separatori);
		c->denumire = (char*)malloc(sizeof(char) * (1 + strlen(element)));
		strcpy(c->denumire, element);

		element = strtok(NULL, separatori);
		c->nrCredite = (int)atoi(element);

		inserareTabela(tabela, c);

	}
	fclose(f);

	traversare(tabela);

}