#include<stdio.h>
#include<stdlib.h>

typedef struct grafo Grafo;
typedef struct aresta Aresta;
typedef struct head Head;
typedef struct pilha Pilha;

struct aresta
{
	int noAdj;
	float peso;
	Aresta* prox;
};

struct grafo
{
	int num_vertices;
	int num_arestas;

	Aresta** arestas;
};

struct head
{
	float dist;
	int visitado;
};

//Funcao que insere arestas em uma lista de adjacencias

Aresta* insereArestas(Aresta* first, int noA, float peso) {
	Aresta* novo = (Aresta*)malloc(sizeof(Aresta));
	if (novo == NULL) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}

	novo->prox = first;
	novo->noAdj = noA;
	novo->peso = peso;

	return novo;
}

//Funcao que cria um grafo e inicializa seu vetor de arestas

Grafo* criaGrafo(int num_vertices, int num_arestas) {
	Grafo* novo = (Grafo*)malloc(sizeof(Grafo));
	if (novo == NULL) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}

	novo->num_arestas = num_arestas;
	novo->num_vertices = num_vertices;

	Aresta** novoArestas = (Aresta**)malloc(num_vertices * sizeof(Aresta*));
	if (novoArestas == NULL) {
		printf("Erro ao alocar memoria\n");
		exit(1);
	}

	novo->arestas = novoArestas;

	for (int i = 0; i < num_vertices; i++) {
		novo->arestas[i] = NULL;
	}

	return novo;
}

//Funcao que encontra o menor valor nao visitado do vetor de distancias

int achaMenor(Head** vet, int tam) {
	int ind = -1, i = 0;
	while (ind < 0) {
		if (i == tam) {
			return -1;
		}
		if (vet[i]->visitado == 0 && vet[i]->dist > 0) {
			ind = i;
		}
		i += 1;
	}

	for (; i < tam; i++) {
		if (vet[i]->dist > 0 && vet[i]->dist < ind && vet[i]->visitado == 0)
			ind = i;
	}
	return ind;
}

//Funcao que cria um vetor de distancias

Head** criaHead(int ini, int tam) {
	Head** head = (Head**)malloc(sizeof(Head*) * tam);
	if (head == NULL) {
		printf("Erro ao alocar memoria");
		exit(1);
	}
	for (int i = 0; i < tam; i++) {
		head[i] = (Head*)malloc(sizeof(Head));

		if (head[i] == NULL) {
			printf("Erro ao alocar memoria");
			exit(1);
		}
		head[i]->visitado = 0;
		head[i]->dist = -1;
	}

	head[ini]->dist = 0;

	return head;
}

//Funcao que calcula o menor caminho ate um vertice seguindo o algoritmo de dijkstra

Head** dijkistra(Grafo* g, int vertice) {
	Head** distVet = criaHead(vertice, g->num_vertices);

	int corrente = vertice;
	int adj = 1; //Variavel auxiliar que conta nos adjacentes nao visitados

	Aresta* p;

	//Calculando o menor caminho ate que nao hajam mais vertices a serem visitados

	while (adj) {
		adj = 0;
		p = g->arestas[corrente];
		while (p != NULL) {
			float distAtual = distVet[p->noAdj]->dist;
			if (distVet[p->noAdj]->visitado == 0) { //Se o no ainda n foi visitado
				adj += 1;
				float distNova = p->peso + distVet[corrente]->dist; //Calcula a nova distancia
				if (distAtual < 0) { //Se o no ainda n tiver distancia setada ou se o a distancia atual for maior q a nova
					distVet[p->noAdj]->dist = distNova;
				}
				else if (distAtual > distNova) {
					distVet[p->noAdj]->dist = distNova;
				}
			}
			p = p->prox;
		}
		distVet[corrente]->visitado = 1; //Marca o no corrente como visitado
		corrente = achaMenor(distVet, g->num_vertices); //Atualiza o no corrente para o de menor distancia
		if (corrente < 0)
			return distVet;
	}
	return distVet;
}

//Funcao que libera vetor de Heads

void liberaHead(Head** h, int tam) {
	for (int i = 0; i < tam; i++) {
		free(h[i]);
	}
	free(h);
}

//Funcao que libera o grafo

void liberaGrafo(Grafo* g) {
	for (int i = 0; i < g->num_vertices; i++) {
		free(g->arestas[i]);
	}
	free(g->arestas);
}

//Funcao que percorre um grafo com percurso em profundidade

void percorreGrafo(Aresta** vetA, int* vis, int vertice) {
	vis[vertice] = 1;
	printf("%Vertice: %d\n", vertice);
	for (Aresta* p = vetA[vertice]; p != NULL; p = p->prox) {
		if (vis[p->noAdj] != 1)
			percorreGrafo(vetA, vis, p->noAdj);
	}
}

int main(void) {

	Grafo* grafo = criaGrafo(7, 13);

	grafo->arestas[0] = insereArestas(grafo->arestas[0], 3, 2);
	grafo->arestas[0] = insereArestas(grafo->arestas[0], 2, 4);
	grafo->arestas[0] = insereArestas(grafo->arestas[0], 1, 5);

	grafo->arestas[1] = insereArestas(grafo->arestas[1], 6, 9);
	grafo->arestas[1] = insereArestas(grafo->arestas[1], 4, 6);
	grafo->arestas[1] = insereArestas(grafo->arestas[1], 2, 6);
	grafo->arestas[1] = insereArestas(grafo->arestas[1], 0, 5);

	grafo->arestas[2] = insereArestas(grafo->arestas[2], 4, 4);
	grafo->arestas[2] = insereArestas(grafo->arestas[2], 3, 3);
	grafo->arestas[2] = insereArestas(grafo->arestas[2], 1, 6);
	grafo->arestas[2] = insereArestas(grafo->arestas[2], 0, 4);

	grafo->arestas[3] = insereArestas(grafo->arestas[3], 5, 9);
	grafo->arestas[3] = insereArestas(grafo->arestas[3], 4, 5);
	grafo->arestas[3] = insereArestas(grafo->arestas[3], 2, 3);
	grafo->arestas[3] = insereArestas(grafo->arestas[3], 0, 2);;

	grafo->arestas[4] = insereArestas(grafo->arestas[4], 6, 6);
	grafo->arestas[4] = insereArestas(grafo->arestas[4], 5, 2);
	grafo->arestas[4] = insereArestas(grafo->arestas[4], 3, 5);
	grafo->arestas[4] = insereArestas(grafo->arestas[4], 2, 4);
	grafo->arestas[4] = insereArestas(grafo->arestas[4], 1, 6);

	grafo->arestas[5] = insereArestas(grafo->arestas[5], 6, 3);
	grafo->arestas[5] = insereArestas(grafo->arestas[5], 4, 2);
	grafo->arestas[5] = insereArestas(grafo->arestas[5], 3, 9);

	grafo->arestas[6] = insereArestas(grafo->arestas[6], 5, 3);
	grafo->arestas[6] = insereArestas(grafo->arestas[6], 4, 6);
	grafo->arestas[6] = insereArestas(grafo->arestas[6], 1, 9);

	int* vis[13];

	percorreGrafo(grafo->arestas, vis, 0);

	printf("\n");

	Head** distVet = dijkistra(grafo, 0);

	for (int i = 0; i < grafo->num_vertices; i++) {
		printf("Vertice: %d\t Distancia: %f\n", i, distVet[i]->dist);
	}

	liberaHead(distVet, grafo->num_vertices);
	liberaGrafo(grafo);

	return 0;
}
