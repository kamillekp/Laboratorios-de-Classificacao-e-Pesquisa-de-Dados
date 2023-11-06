#include <bits/stdc++.h>

using namespace std;

int vetor[1000000];

int partition_hoare(int C[], int left, int right, int *swaps);
void quicksort(int c[], int i, int f, int *recursoes, int *swaps);

int main(){
    int tamanho_vetor, start, end, swaps = 0, recursoes = 0;
    double result;

    while (cin >> tamanho_vetor) {
        cout << "\nNumero de elementos na entrada: " << tamanho_vetor << endl;
        for (int i = 0; i < tamanho_vetor; i++) {
            scanf("%d", &vetor[i]);
        }

        start = clock();
        quicksort(vetor, 0, (tamanho_vetor - 1), &recursoes, &swaps);
        end = clock();

        result = (double) (end - start) / CLOCKS_PER_SEC;

        cout << "Tempo de execucao: " << result * 1000 << " milissegundos" << endl;

        cout << "TAMANHO ENTRADA " << tamanho_vetor << endl; 
        cout << "SWAPS " << swaps << endl;
        cout << "RECURSOES " << recursoes << endl;
        cout << "TEMPO " << result * 1000 << " MILISEGUNDOS" << endl;

        cout << "\n";
    }

    return 0;
}

int partition_hoare(int C[], int left, int right, int *swaps) {
    int chave, i, j;
    chave = C[left]; i = left; j = right+1;

    while (1) {
        while (C[++i] <= chave) if (i == right) break;
            while (chave < C[--j]) if (j == left) break;
                if (i >=j) break;
                    (*swaps)++;
                    swap(C[i],C[j]);
    }

   (*swaps)++;
    swap(C[left], C[j]);
    return j;
}

void quicksort(int c[], int i, int f, int *recursoes, int *swaps){
    int p;

    if(f > i){
        int media = (i + f) / 2;

        if(c[f] > c[i] && c[f] < c[media])
            swap(c[f], c[i]);
        else if(c[media] > c[i] && c[media] < c[f])
            swap(c[media], c[i]);
        
        (*swaps)++;
        (*recursoes)++;

        p = partition_hoare(c, i, f, swaps);
        quicksort(c, i, p-1, recursoes, swaps);
        quicksort(c, p+1, f, recursoes, swaps);
    }
}
