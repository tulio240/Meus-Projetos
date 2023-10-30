#include "Huffman.h"

struct no
{
	char chave;
	int valor;
	No* esq;
	No* dir;
	No* prox;
};

No* criaLista() {
	return NULL;
}

No* criaAb() {
	return NULL;
}

No* insereOrdLista(No* lista, No* elem) {
	No* ant = NULL;
	No* p = lista;

	while (p != NULL && p->valor <= elem->valor)
	{
		ant = p;
		p = p->prox;
	}

	if (ant == NULL) {
		elem->prox = lista;
		return elem;
	}
	if (p == NULL) {
		ant->prox = elem;
		return lista;
	}

	ant->prox = elem;
	elem->prox = p;

	return lista;
}

void insereVet(No** vet, char letra, char* ordemChegada, int* nCaracs) {
	if (vet[letra] == 0) {
		No* novo = (No*)malloc(sizeof(No));

		if (novo == NULL) {
			printf("Erro na alocacao dinamica");
			exit(1);
		}

		novo->chave = letra;
		novo->valor = 1;
		novo->prox = NULL;
		novo->esq = NULL;
		novo->dir = NULL;

		vet[letra] = novo;

		ordemChegada[*nCaracs] = letra;
		*(nCaracs) = *(nCaracs)+1;

		return;
	}

	vet[letra]->valor += 1;
	return;
}

void exibeLista(No* lista) {

	No* p = lista;

	while (p != NULL)
	{
		printf("Valor: %d,  Letra: %c\n", p->valor, p->chave);
		p = p->prox;
	}
}

No* montaAB(No* lista) {

	No* p = lista;
	No* ab = criaAb();

	while (p->prox != NULL) {

		No* prim = p;
		No* sec = prim->prox;

		No* novo = (No*)malloc(sizeof(No));

		if (novo == NULL) {
			printf("Erro na alocacao dinamica");
			exit(1);
		}

		novo->chave = '™';
		novo->valor = prim->valor + sec->valor;
		novo->prox = NULL;
		novo->esq = prim;
		novo->dir = sec;

		p = sec->prox;
		p = insereOrdLista(p, novo);

	}

	return p;
}

void exibeAB(No* ab) {

	if (ab == NULL) {
		return;
	}

	printf("\nValor: %d Chave: %c", ab->valor, ab->chave);
	printf("{");
	exibeAB(ab->esq);
	exibeAB(ab->dir);
	printf("}");
}

void contabilizaAB(No* ab, char** vet, char* cod, char nivel) {
	if (ab->dir == NULL && ab->esq == NULL) {
		vet[ab->chave] = (char*)malloc(sizeof(char) * nivel);
		strcpy(vet[ab->chave], cod);
		return;
	}
	char* esq = (char*)malloc(sizeof(char) * (nivel + 2));
	char* dir = (char*)malloc(sizeof(char) * (nivel + 2));
	if (esq == NULL) {
		printf("Erro ao alocar memoria");
		exit(1);
	}
	if (dir == NULL) {
		printf("Erro ao alocar memoria");
		exit(1);
	}
	strcpy(esq, cod);
	strcpy(dir, cod);

	if (nivel != 0)
		free(cod);

	strcat(esq, "0");
	strcat(dir, "1");

	nivel += 1;

	contabilizaAB(ab->esq, vet, esq, nivel);

	contabilizaAB(ab->dir, vet, dir, nivel);
}

void escreveCompact(FILE* arqLeitura, FILE* arqbin, char** vet) {
	unsigned char word = 0x00;
	char letra;
	char* arr;
	int cont = 0;
	while (!feof(arqLeitura)) {
		if (fscanf(arqLeitura, "%c", &letra) == 1) {
			arr = vet[letra];
			while (*arr) {
				if (*arr == '1') {
					word = word | 0x01;
				}

				cont += 1;
				arr = (arr + 1);
				if (cont > 7) {
					fwrite(&word, sizeof(char), 1, arqbin);
					cont = 0;
					word = 0x00;
				}

				word = word << 1;
			}
		}
	}
	fclose(arqLeitura);
	
	word = word << (8 - cont);

	fwrite(&word, sizeof(char), 1, arqbin);

	fclose(arqbin);
}

void liberaAb(No* ab) {
	if (ab->esq == NULL && ab->dir == NULL) {
		free(ab);
		return;
	}
	liberaAb(ab->esq);
	liberaAb(ab->dir);
	free(ab);
}