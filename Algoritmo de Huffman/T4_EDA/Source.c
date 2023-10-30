#include"Huffman.h"

int main(void) {
	FILE* arqLeitura = fopen("texto.txt", "r");
	if (arqLeitura == NULL) {
		printf("Erro ao abrir o arquivo");
		exit(1);
	}

	No* lista = criaLista();

	char letra;
	char ordemChegada[128];
	int nCaracs = 0;

	No** vet = (No**)calloc(128, sizeof(No*));
	if (vet == NULL) {
		printf("Erro ao abrir o arquivo");
		exit(1);
	}

	//Preenchendo o vetor de nós e atualizando a ordem de chegada

	while (!feof(arqLeitura)) {
		if (fscanf(arqLeitura, "%c", &letra) == 1) {
			insereVet(vet, letra, ordemChegada, &nCaracs);
		}
	}
	fclose(arqLeitura);

	//Montando a lista ordenada a partir dos valores de recorrencia contabilizados em insereVet

	for (int i = 0; i < nCaracs; i++) {
		lista = insereOrdLista(lista, vet[ordemChegada[i]]);
	}

	exibeLista(lista);

	//Montando a árvore binaria

	lista = montaAB(lista);

	exibeLista(lista);

	exibeAB(lista);

	//Pegando o código para cada caracter

	printf("\n\n");

	//char* vetCod[128];
	char** vetCod = (char**)calloc(128, sizeof(char*));
	if (vetCod == NULL) {
		printf("Erro ao abrir o arquivo");
		exit(1);
	}

	char* cod = "";
	char nivel = 0;

	contabilizaAB(lista, vetCod, cod, nivel);

	//Impressao dos codigos 'comprimidos' de cada caracter

	for (int i = 0; i < nCaracs; i++) {
		printf("Chave: %c, Codigo: %s\n", ordemChegada[i], vetCod[ordemChegada[i]]);
	}

	//Releitura do arquivo de entrada para codificacao

	arqLeitura = fopen("texto.txt", "r");
	if (arqLeitura == NULL) {
		printf("Erro ao abrir o arquivo");
		exit(1);
	}

	//Criacao do arquivo binario (arquivo compactado)

	FILE* arqComprimido = fopen("comp.dat", "wb");
	if (arqLeitura == NULL) {
		printf("Erro ao criar o arquivo");
		exit(1);
	}

	escreveCompact(arqLeitura, arqComprimido, vetCod);

	liberaAb(lista);

	free(vet);

	return 0;
}
