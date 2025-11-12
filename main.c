#include "ordenar.h"
#include <time.h>
#include <string.h>

// testarMetodo trabalha com funções do tipo int *fun(int *vetor)
void testarMetodo(const char *nomeMetodo, int *(*funcaoOrdenar)(int *)) {
    int *vetor, *vetorDecr, *vetorEspecial1, *vetorEspecial2;
    double tempo1, tempo2, tempo3, tempo4, tempo5;
    clock_t inicio, fim;

    vetor = criarVetor();
    preencher(vetor);

    printf("\n===============================");
    printf("\n>>> Metodo: %s\n", nomeMetodo);
    printf("===============================\n");

    // Vetor aleatório
    printf("\n\t> Ordernar array aleatorio\n");
    //exibir(vetor);
    inicio = clock();
    funcaoOrdenar(vetor);
    fim = clock();
    tempo1 = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Vetor ordenado (vetor já está ordenado após primeira chamada)
    printf("\n\t> Ordernar array ordenado\n");
    //exibir(vetor);
    inicio = clock();
    funcaoOrdenar(vetor);
    fim = clock();
    tempo2 = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Vetor decrescente
    vetorDecr = inverterVetor(vetor);
    printf("\n\t> Ordernar array decrescente\n");
    //exibir(vetorDecr);
    inicio = clock();
    funcaoOrdenar(vetorDecr);
    fim = clock();
    tempo3 = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Metade crescente / metade decrescente
    vetorDecr = inverterVetor(vetor);
    vetorEspecial1 = criarVetorEsp1(vetor, vetorDecr);
    printf("\n\t> Ordernar array primeira metade cresc. e segunda metade decre.\n");
    //exibir(vetorEspecial1);
    inicio = clock();
    funcaoOrdenar(vetorEspecial1);
    fim = clock();
    tempo4 = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Metade decrescente / metade crescente
    vetorDecr = inverterVetor(vetor);
    vetorEspecial2 = criarVetorEsp2(vetor, vetorDecr);
    printf("\n\t> Ordernar array primeira metade decre. e segunda metade cresc.\n");
    //exibir(vetorEspecial2);
    inicio = clock();
    funcaoOrdenar(vetorEspecial2);
    fim = clock();
    tempo5 = (double)(fim - inicio) / CLOCKS_PER_SEC;

    exibirTempo(tempo1, tempo2, tempo3, tempo4, tempo5);

    free(vetor);
    free(vetorDecr);
    free(vetorEspecial1);
    free(vetorEspecial2);
}

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    srand((unsigned) time(NULL));

    printf("\n===============================");
    printf("\n>>>> TESTES DE METODOS DE ORDENACAO <<<<");
    printf("\n >>> Tamanho do vetor: %d elementos <<<", TAM);
    printf("\n===============================\n");

    // Chama testarMetodo para os 16 algoritmos
    //testarMetodo("Selection Sort", selectionSort);
    //testarMetodo("Insertion Sort", insertionSort);
    //testarMetodo("Bubble Sort", bubbleSort);
    //testarMetodo("Comb Sort", combSort);
    //testarMetodo("Quick Sort", quickSort);
    //testarMetodo("Merge Sort", mergeSort);
    //testarMetodo("Shell Sort", shellSort);
    //testarMetodo("Heap Sort", heapSort);
    //testarMetodo("Radix Sort", radixSort);
    //testarMetodo("Counting Sort", countingSort);
    //testarMetodo("Bucket Sort", bucketSort);
    //testarMetodo("Cocktail Sort", cocktailSort);
    //testarMetodo("Tim Sort", timSort);
    //testarMetodo("Intro Sort", introSort);
    //testarMetodo("Pancake Sort", pancakeSort);
    testarMetodo("Pigeonhole Sort", pigeonholeSort);

    printf("\n===============================");
    printf("\n>>> FIM DOS TESTES <<<");
    printf("\n===============================\n");

    return 0;
}
