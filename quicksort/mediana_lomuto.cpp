#include <bits/stdc++.h>

using namespace std;

int vetor[1000000];

int partition_lomuto(int C[], int left, int right, int *swaps);
void quicksort(int c[], int i, int f, int *swaps, int *recursoes);

int main(){
    int tamanho_vetor, start, end, swaps = 0, recursoes = 1;
    double result;

    while (cin >> tamanho_vetor) {
        for (int i = 0; i < tamanho_vetor; i++) {
            scanf("%d", &vetor[i]);
        }

        start = clock();
        quicksort(vetor, 0, (tamanho_vetor - 1), &swaps, &recursoes);
        end = clock();

        result = (double) (end - start) / CLOCKS_PER_SEC;

        cout << "TAMANHO ENTRADA " << tamanho_vetor << endl; 
        cout << "SWAPS " << swaps << endl;
        cout << "RECURSOES " << recursoes << endl;
        cout << "TEMPO " << result * 1000 << " MILISEGUNDOS" << endl;

        cout << "\n";
    }

    return 0;
}

int partition_lomuto(int C[], int left, int right, int *swaps){
    int chave = C[left];
    int storeindex = left + 1; 

    for (int i = left+1; i <= right; i++) {
        if (C[i] < chave){
            (*swaps)++;
            swap(C[i], C[storeindex]);
            storeindex++; 
        }
    }

    (*swaps)++;
    swap(C[left], C[storeindex-1]);

    return (storeindex-1);
}

void quicksort(int c[], int i, int f, int *swaps, int *recursoes){
    int p;

    if(f > i){
        int media = (i + f) / 2;

        if(c[f] > c[i] && c[f] < c[media])
            swap(c[f], c[i]);
        else if(c[media] > c[i] && c[media] < c[f])
            swap(c[media], c[i]);
        
        (*swaps)++;
        (*recursoes)++;
        p = partition_lomuto(c, i, f, swaps);
        quicksort(c, i, p-1, swaps, recursoes);
        quicksort(c, p+1, f, swaps, recursoes);
    }
}
