#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARINING
#pragma warning(disable:4996)

typedef struct {
	char* denumire;
	int nrCredite;
}Produs;

struct nodAVL{
	int codCurs;
	Produs inf;
	struct nodAVL* stanga, * dreapta;
	char BF;
};

typedef struct nodAVL nodAVL;

int maxim(int a, int b) {
	if (a >= b)
		return a;
	else
		return b;
}

int inaltime(nodAVL* rad) {
	if (rad != NULL) {
		return 1 + maxim(inaltime(rad->stanga), inaltime(rad->dreapta));
	}
	else {
		return 0;
	}
}

void calculeazaBF(nodAVL* rad) {
	if (rad) {
		rad->BF = inaltime(rad->dreapta) - inaltime(rad->stanga);
	}
}

//rotire simpla la dreapta
nodAVL* rotireDreapta(nodAVL* pivot, nodAVL* fiuStanga) {
	pivot->stanga = fiuStanga->dreapta;
	calculeazaBF(pivot);
	fiuStanga->dreapta = pivot;
	calculeazaBF(fiuStanga);

	return fiuStanga;
}


//rotire simpla la stanga                   ----- o folosim la dezechilibru la dreapta
nodAVL* rotireStanga(nodAVL* pivot, nodAVL* fiuDreapta) {
	pivot->dreapta = fiuDreapta->stanga;
	calculeazaBF(pivot);
	fiuDreapta->stanga = pivot;
	calculeazaBF(fiuDreapta);

	return fiuDreapta;
}


//rotie dubla dreapta-stanga            ---- o folosim la dezechilibru dreapta-stanga
nodAVL* rotireDreaptaStanga(nodAVL* pivot, nodAVL* fiuDreapta) {
	pivot->dreapta = rotireDreapta(fiuDreapta, fiuDreapta->stanga);
	calculeazaBF(pivot);

	fiuDreapta = pivot->dreapta;
	fiuDreapta = rotireStanga(pivot, fiuDreapta);
	calculeazaBF(fiuDreapta);

	return fiuDreapta;
}


//rotatie dubla stanga-dreapta
nodAVL* rotireStangaDreapta(nodAVL* pivot, nodAVL* fiuStanga) {
	pivot->stanga = rotireStanga(fiuStanga, fiuStanga->dreapta);
	calculeazaBF(pivot);
	
	fiuStanga = pivot->stanga;
	fiuStanga = rotireDreapta(pivot, fiuStanga);
	calculeazaBF(fiuStanga);

	return fiuStanga;
}



nodAVL* reechilibrare(nodAVL* rad) {
	calculeazaBF(rad);
	if (rad->BF == 2) {
		if (rad->dreapta->BF == 1)
		{
			//dezechilibru dreapta
			rad = rotireStanga(rad, rad->dreapta);
		}
		else {
			//dezechilibru dreapta-stanga
			rad = rotireDreaptaStanga(rad, rad->dreapta);
		}

	}
	else if (rad->BF == -2) {
		if (rad->BF == -1) {
			//dezechilibru stanga
			rad = rotireDreapta(rad, rad->stanga);
		}
		else {
			//dezechilibru stanga-dreapta
			rad = rotireStangaDreapta(rad, rad->stanga);
		}
	}

	return rad;
}


nodAVL* creareNod(Produs c, int cod, nodAVL* stanga, nodAVL* dreapta) {

	nodAVL* nou = (nodAVL*)malloc(sizeof(nodAVL));
	nou->inf.denumire = (char*)malloc(sizeof(char) * (1 + strlen(c.denumire)));
	strcpy(nou->inf.denumire, c.denumire);

	nou->inf.nrCredite = c.nrCredite;

	nou->stanga = stanga;
	nou->dreapta = dreapta;
	nou->codCurs = cod;

	return nou;
}


nodAVL* inserareNod(nodAVL* rad, int cod, Produs curs, int* inserat) { //inserat va fi 0 sau 1 pentru a ne arata daca s a inserat sau nu. Putea fi si char
	if (rad != NULL) {
		if (cod > rad->codCurs) {
			rad->dreapta = inserareNod(rad->dreapta, cod, curs, inserat);
		}
		if (cod < rad->codCurs) {
			rad->stanga = inserareNod(rad->stanga, cod, curs, inserat);
		}
		else if(rad->codCurs==cod) {
			(*inserat) = 0; // cursul nu poate fi inserat pentru ca mai exista deja unul cu acelasi cod
		}
	}
	else {
		rad = creareNod(curs, cod, NULL, NULL);
		(*inserat) = 1;
	}

	//verificam si echilibram arborele daca e cazul
	rad = reechilibrare(rad);
	
	return rad;
}


void afisareInordine(nodAVL* rad) {
	if (rad != NULL) {
		afisareInordine(rad->stanga);
		printf("Cod curs = %d, denumire = %s, numar credite = %d\n", rad->codCurs, rad->inf.denumire, rad->inf.nrCredite);
		afisareInordine(rad->dreapta);
		
	}
}


nodAVL* stergereNodDupaCheie(nodAVL* rad, int cod, Produs* pdata) {
	if (rad) {
		if (rad->codCurs < cod) {
			rad->dreapta = stergereNodDupaCheie(rad->dreapta, cod, pdata);
		}
		else if (rad->codCurs > cod) {
			rad->stanga = stergereNodDupaCheie(rad->stanga, cod, pdata);
		}
		else {
			if ((rad->stanga != NULL) && (rad->dreapta != NULL)) {
				nodAVL* parinte_temp = NULL;
				nodAVL* temp = rad->stanga;
				while (temp->dreapta != NULL) {
					parinte_temp = temp;
					temp = temp->dreapta;
				}

				int aux = rad->codCurs;
				rad->codCurs = temp->codCurs;
				temp->codCurs = aux;

				Produs curs = rad->inf;
				rad->inf = temp->inf;

				nodAVL* desc_temp_stanga = temp->stanga;

				*pdata = temp->inf;
				free(temp);

				if (parinte_temp != NULL) {
					parinte_temp->dreapta = desc_temp_stanga;
				}
				else {
					rad->stanga = desc_temp_stanga;
				}

			}
			else {
				nodAVL* temp = NULL;
				if (rad->stanga != NULL) {
					temp = rad->stanga;
				}
				else if (rad->dreapta != NULL) {
					temp = rad->dreapta;
				}

				*pdata = rad->inf;
				free(rad);

				rad = temp;
			}
			rad = reechilibrare(rad);
		}
	}
	return rad;
}


void afiseazaBine(nodAVL* rad) {
	if (rad!=NULL) {
		printf("rad %d\n", rad->codCurs);
		if (rad->dreapta!=NULL)
		{
			printf("dreapta %d\n", rad->dreapta->codCurs);
		}
		if(rad->stanga!=NULL)
		{
			printf("stanga %d\n", rad->stanga->codCurs);
		}
		printf("---\n");
		afiseazaBine(rad->dreapta);
		afiseazaBine(rad->stanga);
	}
	
}



void main() {
	FILE* f = fopen("FisierAVL.txt", "r");
	nodAVL* rad = NULL;

	char linie[256];
	char separatori[] = ";\n";

	while (fgets(linie, sizeof(linie), f) ){
		Produs curs;
		int codCurs;

		char* element = NULL;

		element = strtok(linie, separatori);
		codCurs = (int)atoi(element);

		element = strtok(NULL, separatori);
		curs.denumire = (char*)malloc(sizeof(char) * (1 + strlen(element)));
		strcpy(curs.denumire, element);

		element = strtok(NULL, separatori);
		curs.nrCredite = (int)atoi(element);

		int inserat = 0;
		rad = inserareNod(rad, codCurs, curs, &inserat);
		if (inserat == 0) {
			printf("inserare esuata pentru nodul cu codul %d\n",codCurs);
		}
		else {
			printf("Am inserat cu succes! %d\n", codCurs);
		}


	}

	afisareInordine(rad);

	printf("\nSTERGEREEEEEEE\n");

	Produs curs1;
	curs1.denumire = NULL;
	rad = stergereNodDupaCheie(rad, 10, &curs1);
	afiseazaBine(rad);

	afisareInordine(rad);

	fclose(f);
}