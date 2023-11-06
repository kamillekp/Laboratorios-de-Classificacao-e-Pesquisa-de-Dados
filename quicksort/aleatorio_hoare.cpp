#include <bits/stdc++.h>

using namespace std;

int vetor[1000000];

int random(int i, int f);   
int partition_hoare(int C[], int left, int right, int *swaps);
void quicksort_randomizado(int c[], int i, int f, int *recursoes, int *swaps);

int main(){
    int tamanho_vetor, start, end, swaps = 0, recursoes = 0;
    double result;

    while (cin >> tamanho_vetor) {
        cout << "\nNumero de elementos na entrada: " << tamanho_vetor << endl;
        for (int i = 0; i < tamanho_vetor; i++) {
            scanf("%d", &vetor[i]);
        }

        start = clock();
        quicksort_randomizado(vetor, 0, (tamanho_vetor - 1), &recursoes, &swaps);
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

int random(int i, int f){
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(i, f); 

    return dist(gen);   
}

int partition_hoare(int C[], int left, int right, int *swaps) {
    int chave, i, j;
    chave = C[left]; i = left; j = right+1;

    while (1) {
        while (C[++i] <= chave) if (i == right) break;
            while (chave < C[--j]) if (j == left) break;
                if (i >=j) 
                    break;
                
                (*swaps)++;
                swap(C[i],C[j]);
    }

    (*swaps)++;
    swap(C[left], C[j]);
    return j;
}

void quicksort_randomizado(int c[], int i, int f, int *recursoes, int *swaps){
    int p, r;

    if(f > i) {
        r = random(i,f);

        (*swaps)++;
        (*recursoes)++;

        swap(c[i], c[r]);
        p = partition_hoare(c,i,f, swaps);
        quicksort_randomizado(c, i, p-1, recursoes, swaps);
        quicksort_randomizado(c, p+1, f, recursoes, swaps);
    }
}
