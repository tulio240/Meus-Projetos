#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no No;

//Funcao para criar uma lista vazia

No* criaLista();

//Funcao para criar uma arvore binaria

No* criaAb();

//Funcao que insere elementos dentro de uma lista de prioridades, respeitando as regras de ordenacao

No* insereOrdLista(No* lista, No* elem);

//Funcao que insere elementos em um vetor e atualiza suas recorrencias

void insereVet(No** vet, char letra, char* ordemChegada, int* nCaracs);

//Funcao que exibe a lista ordenada

void exibeLista(No* lista);

//Funcao que monta a arvore binaria para a compressao de Huffman a partir da lista ordenada

No* montaAB(No* lista);

//Funcao que exibe a arvore binaria

void exibeAB(No* ab);

//Funcao que cria os codigos para cada caractere a partir da leitura da arvore binaria, colocando-os em vetor

void contabilizaAB(No* ab, char** vet, char* cod, char nivel);

//Funcao que escreve o arquivo binario substituindo as ocorrencias de cada letra por seu codigo comprimido

void escreveCompact(FILE* arqLeitura, FILE* arqbin, char** vet);

//Funcao que libera a memoria alocada para os nos da arvore

void liberaAb(No* ab);