#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>     
#include <string.h>   

/* --- 1. Insertion Sort ---
    - É um método simples que ordena sem usar vetor extra grande).
*/

void insertion(int *A, int n) {
     int i, chave, j;
     // Começamos em i = 1 porque o primeiro elemento (índice 0) já é considerado "ordenado"
     for (i = 1; i < n; i++) {
          chave = A[i];    // "chave" é o elemento que queremos inserir na parte ordenada à esquerda
          j = i - 1;       // j aponta para o último elemento da parte ordenada

          // Enquanto não chegarmos ao início e o elemento atual for maior que a chave,
          // deslocamos esse elemento uma posição para a direita para abrir espaço.
          while (j >= 0 && A[j] > chave) {
                A[j + 1] = A[j]; // move A[j] para a direita
                j = j - 1;       // avança para o próximo elemento da parte ordenada (à esquerda)
          }

          // Aqui j parou na posição anterior à correta, então inserimos a chave em j+1
          A[j + 1] = chave;
     }
}

// --- 2. Mergesort ---
// Implementação recursiva do mergesort em um único vetor A de tamanho n.
void mergesort2(int *A, int n) {
    // Caso base: se o vetor tem 0 ou 1 elemento já está ordenado
    if (n < 2) {
        return;
    }

    // Dividir: calcular o meio para separar em duas metades
    int meio = n / 2;

    // Conquistar: chamar mergesort recursivamente para cada metade
    // A ---------- A+meio
    // [0..meio-1] e [meio..n-1]
    mergesort2(A, meio);
    mergesort2(A + meio, n - meio);

    // Combinar (merge): vamos unir as duas metades que já estão ordenadas
    // Criamos um vetor auxiliar B para guardar o resultado do merge
    int *B = (int *)malloc(n * sizeof(int));

    // i percorre a primeira metade (0..meio-1)
    int i = 0;
    // j percorre a segunda metade (meio..n-1)
    int j = meio;
    // k é o índice atual no vetor auxiliar B
    int k = 0;

    // Enquanto houver elementos em ambas as metades, copiamos o menor
    while (i < meio && j < n) {
        if (A[i] < A[j]) {
            B[k++] = A[i++]; // pega da primeira metade
        } else {
            B[k++] = A[j++]; // pega da segunda metade
        }
    }

    // Se sobrou coisa na primeira metade, copia tudo para B
    while (i < meio) {
        B[k++] = A[i++];
    }
    // Se sobrou coisa na segunda metade, copia tudo para B
    while (j < n) {
        B[k++] = A[j++];
    }

    // Agora B tem os n elementos ordenados. Copiamos de volta para A.
    // Poderíamos usar memcpy, mas aqui fazemos com um for para ficar claro.
    for (k = 0; k < n; k++) {
        A[k] = B[k];
    }

    // Liberar a memória auxiliar que criamos
    free(B);
}

// --- 3. Quicksort ---
// Comentários explicam ideia geral e cada passo de forma direta e sem muitos detalhes teóricos.

// Função auxiliar para trocar dois inteiros apontados por ponteiros.
void trocar(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função para particionar o subvetor A[inicio..fim].
// Aqui escolhemos o último elemento como pivô (pivo_valor = A[fim]).
// A ideia: colocar no fim do processo o pivô na posição correta,
// com todos os elementos menores à esquerda e os maiores à direita.
// Retorna o índice final do pivô.
int particionar(int *A, int inicio, int fim) {
    int pivo_valor = A[fim];      // pivô = último elemento do subvetor
    int i = (inicio - 1);         // i marca a posição do último elemento menor que o pivô

    // Percorremos do início até o elemento antes do pivô
    for (int j = inicio; j <= fim - 1; j++) {
        // Se o elemento atual for menor que o pivô, movemos ele para a "parte menor"
        if (A[j] < pivo_valor) {
            i++;                  // avança i para abrir espaço
            trocar(&A[i], &A[j]); // troca para colocar A[j] na posição correta (à esquerda)
        }
    }
    // Coloca o pivô logo após a última posição menor encontrada (i+1)
    trocar(&A[i + 1], &A[fim]);
    return (i + 1); // índice onde o pivô ficou
}

// Função recursiva que aplica QuickSort no intervalo A[inicio..fim].
void quicksort_recursivo(int *A, int inicio, int fim) {
    if (inicio < fim) {
        int pi = particionar(A, inicio, fim); // particiona e pega posição do pivô
        // Ordena recursivamente a parte esquerda do pivô
        quicksort_recursivo(A, inicio, pi - 1);
        // Ordena recursivamente a parte direita do pivô
        quicksort_recursivo(A, pi + 1, fim);
    }
}

// Função principal  que recebe o vetor A e seu tamanho n.
// Apenas chama a versão recursiva com os índices corretos (0 a n-1).
void quicksort(int *A, int n) {
    if (n <= 1) return; // se tiver 0 ou 1 elemento, já está ordenado
    quicksort_recursivo(A, 0, n - 1);
}



// Gera um vetor em ordem crescente: A[0]=0, A[1]=1, ..., A[n-1]=n-1
void gerar_vetor_crescente(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i; // preenche com valores crescentes simples
    }
}

// Gera um vetor em ordem decrescente: A[0]=n-1, A[1]=n-2, ..., A[n-1]=0
void gerar_vetor_decrescente(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = (n - 1) - i; // calcula a posição invertida
    }
}

// Gera um vetor com valores aleatórios usando rand().
void gerar_vetor_aleatorio(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand(); // valor aleatório inteiro
    }
}



int main() {
    // Inicializa a seed para números aleatórios
    srand(time(NULL));

    // Abre o arquivo CSV para salvar os resultados
    FILE *arquivo_csv = fopen("resultados.csv", "w");
    if (arquivo_csv == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return 1;
    }
    // 'insere' o cabeçalho do CSV
    fprintf(arquivo_csv, "algoritmo,tipo_vetor,tamanho_n,tempo_gasto_s\n");

    // Define os tamanhos de 'n' para testar
    int tamanhos[] = {24000, 26000, 28000, 30000, 32000, 34000, 36000, 38000, 40000};
    int num_tamanhos = 9;

    // configura os nomes de tipos e algoritmos para salvar no CSV
    char *nomes_algos[] = {"InsertionSort", "MergeSort", "QuickSort"};
    char *nomes_tipos[] = {"Crescente", "Decrescente", "Aleatorio"};

    printf("Comecando a rodar o codigo, aguarde.\n");

    // Laço 1 (Externo): Itera sobre os TAMANHOS
    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        printf("Teste para n = %d...\n", n);

        // Aloca memória para os vetores
        int *vetor_original = (int *)malloc(n * sizeof(int));
        int *vetor_copia = (int *)malloc(n * sizeof(int));

        // Laço 2: Itera sobre os TIPOS DE VETOR (0=cresc, 1=decr, 2=aleat)
        for (int tipo = 0; tipo < 3; tipo++) {
            
            // Gera o vetor original de acordo com o tipo
            if (tipo == 0) gerar_vetor_crescente(vetor_original, n);
            else if (tipo == 1) gerar_vetor_decrescente(vetor_original, n);
            else gerar_vetor_aleatorio(vetor_original, n);

            // Laço 3 (Interno): Itera sobre os ALGORITMOS (0=insert, 1=merge, 2=quick)
            for (int algo = 0; algo < 3; algo++) {
                
                // Copia o vetor original para o vetor_copia
                memcpy(vetor_copia, vetor_original, n * sizeof(int));

                clock_t inicio, fim;
                double tempo_gasto;

                // --- Inicia a medição ---
                inicio = clock();

                if (algo == 0) insertion(vetor_copia, n);
                else if (algo == 1) mergesort2(vetor_copia, n);
                else if (algo == 2) quicksort(vetor_copia, n);

                fim = clock();
                // --- Termina a medição ---

                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                // Salva os dados no arquivo CSV
                fprintf(arquivo_csv, "%s,%s,%d,%f\n", 
                        nomes_algos[algo], nomes_tipos[tipo], n, tempo_gasto);
            }
        }

        // Libera a memória alocada para este 'n'
        free(vetor_original);
        free(vetor_copia);
    }

    // Fecha o arquivo CSV
    fclose(arquivo_csv);

    printf("Codigo concluido! Resultados salvos em 'resultados.csv'.\n");

    return 0;
}