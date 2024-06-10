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

typedef struct{
	Curs inf;
	struct nodStiva* next;
}nodStiva;

typedef struct {
	Curs inf;
	struct nodCoada* next;
}nodCoada;

nodStiva* push(nodStiva* varf, Curs c) {

	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.codCurs = c.codCurs;
	nou->inf.denumire = (char*)malloc(sizeof(char) * (1 + strlen(c.denumire)));
	strcpy(nou->inf.denumire, c.denumire);
	nou->inf.nrCredite = c.nrCredite;
	nou->next = NULL;

	if (varf == NULL) {
		varf = nou;
	}
	else {
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(nodStiva** varf, Curs* c) {
	if ((*varf) != NULL) {
		(*c).codCurs = (*varf)->inf.codCurs;
		(*c).denumire = (char*)malloc(sizeof(char) * (1 + strlen((*varf)->inf.denumire)));
		strcpy((*c).denumire, (*varf)->inf.denumire);

		(*c).nrCredite = (*varf)->inf.nrCredite;

		nodStiva* temp = (*varf);
		(*varf) = (*varf)->next;

		free(temp->inf.denumire);
		free(temp);

		return 0;
	}
	else {
		return -1;
	}
	
}

void put(nodCoada** prim, nodCoada** ultim, Curs c) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.codCurs = c.codCurs;
	nou->inf.denumire = (char*)malloc(sizeof(char) * (1 + strlen(c.denumire)));
	strcpy(nou->inf.denumire, c.denumire);
	nou->inf.nrCredite = c.nrCredite;
	nou->next = NULL;

	if ((*prim) == NULL || (*ultim) == NULL) {
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}

}

int get(nodCoada** prim, nodCoada** ultim, Curs* c) {
	if ((*prim) != NULL) {
		(*c).codCurs = (*prim)->inf.codCurs;
		(*c).denumire = (char*)malloc(sizeof(char) * (1 + strlen((*prim)->inf.denumire)));
		strcpy((*c).denumire, (*prim)->inf.denumire);

		(*c).nrCredite = (*prim)->inf.nrCredite;

		nodCoada* temp = (*prim);
		(*prim) = (*prim)->next;
		free(temp->inf.denumire);
		free(temp);

		return 0;
	}
	else if((*prim)==NULL){
		(*ultim) = NULL;
		return -1;
	}

}

void traversareStiva(nodStiva* varf) {
	if (varf != NULL) {
		while (varf) {
			printf("Cod = %d, Denumire = %s, Nr credite = %d\n", varf->inf.codCurs, varf->inf.denumire, varf->inf.nrCredite);
			varf = varf->next;
		}
	}
}

void traversareCoada(nodCoada* prim) {
	while (prim) {
		printf("Cod = %d, Denumire = %s, Nr credite = %d\n", prim->inf.codCurs, prim->inf.denumire, prim->inf.nrCredite);
		prim = prim->next;
	}
}

void conversieStivaCoada(nodStiva* varf, nodCoada** prim, nodCoada** ultim) {
	Curs c;
	while (pop(&varf, &c) == 0) {
		put(prim, ultim, c);
	}
}

//void conversieCoadaStiva(nodCoada** prim, nodCoada** ultim, nodStiva** varf) {
//	Curs c;
//	while (get(prim, ultim, &c) == 0) {
//		*varf = push((*varf), c);
//	}
//}

void main() {
	FILE* f = fopen("FisierAVL.txt", "r");

	nodStiva* varf = NULL;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;

	char linie[256];
	char separatori[] = ";\n";

	while (fgets(linie, sizeof(linie), f)) {
		Curs curs;

		char* element = NULL;

		element = strtok(linie, separatori);
		curs.codCurs = (int)atoi(element);

		element = strtok(NULL, separatori);
		curs.denumire = (char*)malloc(sizeof(char) * (1 + strlen(element)));
		strcpy(curs.denumire, element);

		element = strtok(NULL, separatori);
		curs.nrCredite = (int)atoi(element);


		varf = push(varf, curs);
		put(&prim, &ultim, curs);



	}
	fclose(f);
	printf("STIVA\n");
	traversareStiva(varf);

	printf("\nCOADA\n");
	traversareCoada(prim);

	printf("\nConversie stiva -> coada\n");
	nodCoada* prim2 = NULL;
	nodCoada* ultim2 = NULL;
	conversieStivaCoada(varf, &prim2, &ultim2);
	traversareCoada(prim2);

	/*printf("\nConversie coada -> stiva\n");
	nodStiva* varf2 = NULL;
	conversieCoadaStiva(&prim, &ultim, &varf2);
	traversareStiva(varf2);*/

}