#include "ordenar.h"

/* ----------------- UTILIDADES ----------------- */
// Função para criar um vetor dinâmico de tamanho TAM
int *criarVetor(){
    int *vetor = malloc(TAM * sizeof(int));
    return vetor;
}
// Função para exibir os elementos do vetor
void exibir(int *vetor){
    for(int i=0; i < TAM; i++) {
        printf(" %d |", vetor[i]);
    }
    printf("\n");
}
// Função auxiliar para formatar o tempo total em horas, minutos e segundos
void exibirTempoFormatado(double segundosTotais) {
    int horas = (int)(segundosTotais / 3600);
    segundosTotais -= horas * 3600;
    int minutos = (int)(segundosTotais / 60);
    segundosTotais -= minutos * 60;
    int segundos = (int)segundosTotais;
    int milissegundos = (int)((segundosTotais - segundos) * 1000);

    printf("Tempo total: %02dh %02dm %02ds %03dms\n",
           horas, minutos, segundos, milissegundos);
}

// Função para exibir os tempos de execução e o tempo total
void exibirTempo(double tempo1, double tempo2, double tempo3, double tempo4, double tempo5) {
    printf("\n\t> Tempos de execucao\n");
    printf("Tempo de ordernar uma array aleatorio: %f sec\n", tempo1);
    printf("Tempo de ordernar uma array ordenado: %f sec\n", tempo2);
    printf("Tempo de ordernar uma array decrescente: %f sec\n", tempo3);
    printf("Tempo de ordernar uma primeira metade cresc. e segunda metade decre.: %f sec\n", tempo4);
    printf("Tempo de ordernar uma primeira metade decre. e segunda metade cresc.: %f sec\n", tempo5);

    // Soma dos tempos individuais
    double tempoTotal = tempo1 + tempo2 + tempo3 + tempo4 + tempo5;

    printf("\n\t> Tempo total de execucao:\n");
    exibirTempoFormatado(tempoTotal);
}


/* ----------------- SELECTION SORT ----------------- */
int *selectionSort(int *vetor){
    int i, j, indiceMenor, temp;
    for (i = 0; i < TAM - 1; i++) {
        indiceMenor = i;
        for (j = i + 1; j < TAM; j++) {
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            temp = vetor[i];
            vetor[i] = vetor[indiceMenor];
            vetor[indiceMenor] = temp;
        }
    }
    return vetor;
}

/* ----------------- INSERTION SORT ----------------- */
int *insertionSort(int *vetor){
    int i, j, key;
    for (i = 1; i < TAM; i++) {
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = key;
    }
    return vetor;
}

/* ----------------- BUBBLE SORT ----------------- */
int *bubbleSort(int *vetor){
    int i, j, temp;
    for (i = 0; i < TAM - 1; i++) {
        for (j = 0; j < TAM - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    return vetor;
}

/* ----------------- COMB SORT ----------------- */
int *combSort(int *vetor){
    int gap = TAM;
    const double shrink = 1.3;
    int sorted = 0;
    while (!sorted) {
        gap = (int)(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = 1;
        }
        int i;
        for (i = 0; i + gap < TAM; i++) {
            if (vetor[i] > vetor[i + gap]) {
                int tmp = vetor[i];
                vetor[i] = vetor[i + gap];
                vetor[i + gap] = tmp;
                sorted = 0;
            }
        }
    }
    return vetor;
}

/* ----------------- QUICK SORT ----------------- */
static int partition_qs(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i+1;
}
static void quickSortRec(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition_qs(arr, low, high);
        quickSortRec(arr, low, pi - 1);
        quickSortRec(arr, pi + 1, high);
    }
}
int *quickSort(int *vetor){
    quickSortRec(vetor, 0, TAM - 1);
    return vetor;
}

/* ----------------- MERGE SORT ----------------- */
static void merge(int *arr, int l, int m, int r, int *temp) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = temp[i];
}
static void mergeSortRec(int *arr, int l, int r, int *temp) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSortRec(arr, l, m, temp);
    mergeSortRec(arr, m + 1, r, temp);
    merge(arr, l, m, r, temp);
}
int *mergeSort(int *vetor){
    int *temp = malloc(TAM * sizeof(int));
    if (!temp) return vetor; // fallback
    mergeSortRec(vetor, 0, TAM - 1, temp);
    free(temp);
    return vetor;
}

/* ----------------- SHELL SORT ----------------- */
int *shellSort(int *vetor){
    for (int gap = TAM/2; gap > 0; gap /= 2) {
        for (int i = gap; i < TAM; i++) {
            int temp = vetor[i];
            int j;
            for (j = i; j >= gap && vetor[j - gap] > temp; j -= gap)
                vetor[j] = vetor[j - gap];
            vetor[j] = temp;
        }
    }
    return vetor;
}

/* ----------------- HEAP SORT ----------------- */
static void heapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}
int *heapSort(int *vetor){
    int n = TAM;
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(vetor, n, i);
    for (int i = n - 1; i >= 0; i--) {
        int tmp = vetor[0]; vetor[0] = vetor[i]; vetor[i] = tmp;
        heapify(vetor, i, 0);
    }
    return vetor;
}

/* ----------------- RADIX SORT (LSD, non-negative) ----------------- */
int *radixSort(int *vetor){
    int max = vetor[0];
    for (int i = 1; i < TAM; i++) if (vetor[i] > max) max = vetor[i];
    int *output = malloc(TAM * sizeof(int));
    if (!output) return vetor;
    for (int exp = 1; max/exp > 0; exp *= 10) {
        int count[10] = {0};
        for (int i = 0; i < TAM; i++) count[(vetor[i]/exp)%10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i-1];
        for (int i = TAM - 1; i >= 0; i--) {
            int idx = (vetor[i]/exp)%10;
            output[--count[idx]] = vetor[i];
        }
        for (int i = 0; i < TAM; i++) vetor[i] = output[i];
    }
    free(output);
    return vetor;
}

/* ----------------- COUNTING SORT (non-negative) ----------------- */
int *countingSort(int *vetor){
    int max = vetor[0];
    for (int i = 1; i < TAM; i++) if (vetor[i] > max) max = vetor[i];
    int range = max + 1;
    if (range <= 0) return vetor;
    int *count = calloc(range, sizeof(int));
    if (!count) return vetor;
    for (int i = 0; i < TAM; i++) count[vetor[i]]++;
    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (count[i]-- > 0) vetor[idx++] = i;
    }
    free(count);
    return vetor;
}

/* ----------------- BUCKET SORT ----------------- */
int *bucketSort(int *vetor){
    int max = vetor[0];
    for (int i = 1; i < TAM; i++) if (vetor[i] > max) max = vetor[i];
    int bucketCount = TAM;
    if (max == 0) return vetor;
    int **buckets = malloc(bucketCount * sizeof(int*));
    int *sizes = calloc(bucketCount, sizeof(int));
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = malloc(TAM * sizeof(int));
        sizes[i] = 0;
    }
    for (int i = 0; i < TAM; i++) {
        int idx = (vetor[i] * bucketCount) / (max + 1);
        if (idx < 0) idx = 0;
        if (idx >= bucketCount) idx = bucketCount - 1;
        buckets[idx][sizes[idx]++] = vetor[i];
    }
    for (int b = 0; b < bucketCount; b++) {
        for (int i = 1; i < sizes[b]; i++) {
            int key = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && buckets[b][j] > key) {
                buckets[b][j+1] = buckets[b][j];
                j--;
            }
            buckets[b][j+1] = key;
        }
    }
    int idx = 0;
    for (int b = 0; b < bucketCount; b++) {
        for (int j = 0; j < sizes[b]; j++) {
            vetor[idx++] = buckets[b][j];
        }
    }
    for (int i = 0; i < bucketCount; i++) free(buckets[i]);
    free(buckets);
    free(sizes);
    return vetor;
}

/* ----------------- COCKTAIL SORT ----------------- */
int *cocktailSort(int *vetor){
    int swapped = 1;
    int start = 0;
    int end = TAM - 1;
    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (vetor[i] > vetor[i+1]) {
                int tmp = vetor[i]; vetor[i] = vetor[i+1]; vetor[i+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
        swapped = 0;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (vetor[i] > vetor[i+1]) {
                int tmp = vetor[i]; vetor[i] = vetor[i+1]; vetor[i+1] = tmp;
                swapped = 1;
            }
        }
        start++;
    }
    return vetor;
}

/* ----------------- TIMSORT (simplificado) ----------------- */
#define RUN 32
static void insertionForTim(int *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}
static void mergeForTim(int *arr, int l, int m, int r, int *temp) {
    int i = l, j = m+1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = temp[i];
}
int *timSort(int *vetor){
    int *temp = malloc(TAM * sizeof(int));
    if (!temp) return vetor;
    for (int i = 0; i < TAM; i += RUN) {
        int right = (i + RUN - 1) < (TAM - 1) ? (i + RUN - 1) : (TAM - 1);
        insertionForTim(vetor, i, right);
    }
    for (int size = RUN; size < TAM; size = 2 * size) {
        for (int left = 0; left < TAM; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2*size - 1) < (TAM - 1) ? (left + 2*size - 1) : (TAM - 1);
            if (mid < right)
                mergeForTim(vetor, left, mid, right, temp);
        }
    }
    free(temp);
    return vetor;
}

/* ----------------- INTRO SORT ----------------- */
static int floor_log2(int n) {
    int r = 0;
    while (n >>= 1) r++;
    return r;
}
static void introHeapSortUtil(int *arr, int start, int end) {
    int n = end - start + 1;
    int *tmp = malloc(n * sizeof(int));
    if (!tmp) return;
    for (int i = 0; i < n; i++) tmp[i] = arr[start + i];
    for (int i = n/2 - 1; i >= 0; i--) {
        int idx = i;
        while (1) {
            int l = 2*idx + 1;
            int r = 2*idx + 2;
            int largest = idx;
            if (l < n && tmp[l] > tmp[largest]) largest = l;
            if (r < n && tmp[r] > tmp[largest]) largest = r;
            if (largest != idx) {
                int t = tmp[idx]; tmp[idx] = tmp[largest]; tmp[largest] = t;
                idx = largest;
            } else break;
        }
    }
    for (int i = n-1; i >= 0; i--) {
        int t = tmp[0]; tmp[0] = tmp[i]; tmp[i] = t;
        int idx = 0;
        while (1) {
            int l = 2*idx + 1;
            int r = 2*idx + 2;
            int largest = idx;
            if (l < i && tmp[l] > tmp[largest]) largest = l;
            if (r < i && tmp[r] > tmp[largest]) largest = r;
            if (largest != idx) {
                int tt = tmp[idx]; tmp[idx] = tmp[largest]; tmp[largest] = tt;
                idx = largest;
            } else break;
        }
    }
    for (int i = 0; i < n; i++) arr[start + i] = tmp[i];
    free(tmp);
}
static void introRec(int *arr, int start, int end, int depthLimit) {
    if (start >= end) return;
    if (depthLimit == 0) {
        introHeapSortUtil(arr, start, end);
        return;
    }
    int pivot = arr[(start + end) / 2];
    int i = start, j = end;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            i++; j--;
        }
    }
    if (start < j) introRec(arr, start, j, depthLimit - 1);
    if (i < end) introRec(arr, i, end, depthLimit - 1);
}
int *introSort(int *vetor){
    int depthLimit = 2 * floor_log2(TAM);
    introRec(vetor, 0, TAM - 1, depthLimit);
    return vetor;
}

/* ----------------- PANCAKE SORT ----------------- */
static void flip(int *arr, int i) {
    int start = 0;
    while (start < i) {
        int tmp = arr[start];
        arr[start] = arr[i];
        arr[i] = tmp;
        start++; i--;
    }
}
int *pancakeSort(int *vetor){
    for (int curr_size = TAM; curr_size > 1; curr_size--) {
        int mi = 0;
        for (int i = 0; i < curr_size; i++)
            if (vetor[i] > vetor[mi]) mi = i;
        if (mi != curr_size - 1) {
            flip(vetor, mi);
            flip(vetor, curr_size - 1);
        }
    }
    return vetor;
}

/* ----------------- PIGEONHOLE SORT ----------------- */
int *pigeonholeSort(int *vetor){
    int min = vetor[0], max = vetor[0];
    for (int i = 1; i < TAM; i++) {
        if (vetor[i] < min) min = vetor[i];
        if (vetor[i] > max) max = vetor[i];
    }
    int range = max - min + 1;
    int *holes = calloc(range, sizeof(int));
    if (!holes) return vetor;
    for (int i = 0; i < TAM; i++) holes[vetor[i] - min]++;
    int idx = 0;
    for (int i = 0; i < range; i++) {
        while (holes[i]-- > 0) vetor[idx++] = i + min;
    }
    free(holes);
    return vetor;
}

/* ----------------- UTILS (preencher, inverter, vetores especiais) ----------------- */
// Função para preencher o vetor com números aleatórios (0..TAM)
void preencher(int *vetor){
    for(int i = 0; i < TAM; i++)
        vetor[i] = rand()% (TAM+1);
}
// Função para inverter a ordem dos elementos do vetor
int *inverterVetor(int *vetor){
    int *vetorDecrescente = criarVetor(), j = 0;
    for(int i = TAM-1; i >= 0; i--){
        vetorDecrescente[j] = vetor[i];
        j++;
    }
    return vetorDecrescente;
}
int *criarVetorEsp1(int *vetorCresc, int *vetorDecre){
    int *novoVetor = criarVetor();
    int c = 0;
    for(int i = 0; i < TAM/2; i++){
        novoVetor[i] = vetorCresc[i];
    }
    for(int i = TAM/2; i < TAM; i++){
        novoVetor[i] = vetorDecre[c];
        c++;
    }
    return novoVetor;
}
int *criarVetorEsp2(int *vetorCresc, int *vetorDecre){
    int *novoVetor = criarVetor();
    int c = TAM/2 - 1;
    for(int i = 0; i < TAM/2; i++){
        novoVetor[i] = vetorCresc[c];
        c--;
    }
    c = TAM/2;
    for(int i = TAM/2; i < TAM; i++){
        novoVetor[i] = vetorDecre[c];
        c--;
    }
    return novoVetor;
}