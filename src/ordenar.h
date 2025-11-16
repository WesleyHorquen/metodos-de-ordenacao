#ifndef ORDENAR_H_INCLUDED
#define ORDENAR_H_INCLUDED
#define INSERTION_THRESHOLD 50

// Define o tamanho do vetor (ajuste se quiser)
#define TAM 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <locale.h>

// Funções utilitárias
int *criarVetor();
void exibir(int *vetor);
void exibirTempo(double tempo1, double tempo2, double tempo3, double tempo4, double tempo5);
void exibirTempoFormatado(double segundosTotais);

// Assinaturas - cada método retorna o mesmo ponteiro passado (ordenado in-place)
int *selectionSort(int *vetor);
int *insertionSort(int *vetor);
int *bubbleSort(int *vetor);
int *combSort(int *vetor);
int *quickSort(int *vetor);
int *mergeSort(int *vetor);
int *shellSort(int *vetor);
int *heapSort(int *vetor);
int *radixSort(int *vetor);
int *countingSort(int *vetor);
int *bucketSort(int *vetor);
int *cocktailSort(int *vetor);
int *timSort(int *vetor);
int *introSort(int *vetor);
int *pancakeSort(int *vetor);
int *pigeonholeSort(int *vetor);

// funções utilitárias expostas
void preencher(int *vetor);
int *inverterVetor(int *vetor);
int *criarVetorEsp1(int *vetorCresc, int *vetorDecre);
int *criarVetorEsp2(int *vetorCresc, int *vetorDecre);

#endif