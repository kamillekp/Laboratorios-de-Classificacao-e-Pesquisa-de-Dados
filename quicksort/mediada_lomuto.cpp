#include <bits/stdc++.h>

using namespace std;

int partition_lomuto(vector <int> C, int left, int right);
void quicksort(vector <int> c, int i, int f);

int main(){
    int tamanho_vetor, start, end, var;
    vector <int> vetor;
    double result;

    while (cin >> tamanho_vetor) {
        cout << "\nNumero de elementos na entrada: " << tamanho_vetor << endl;
        for (int i = 0; i < tamanho_vetor; i++) {
            scanf("%d", &var);
            vetor.push_back(var);
        }

        start = clock();
        quicksort(vetor, 0, (tamanho_vetor - 1));
        end = clock();

        result = (double) (end - start) / CLOCKS_PER_SEC;

        cout << "Tempo de execucao: " << result * 1000 << " milissegundos" << endl;

        vetor.clear();
    }

    return 0;
}

int partition_lomuto(vector <int> C, int left, int right){
    int chave = C[left];
    int storeindex = left + 1; 

    for (int i = left+1; i <= right; i++) {
        if (C[i] < chave){
            swap(C[i], C[storeindex]);
            storeindex++; 
        }
    }

    swap(C[left], C[storeindex-1]);

    return (storeindex-1);
}

void quicksort(vector <int> c, int i, int f){
    int p;

    if(f > i){
        p = partition_lomuto(c, i, f);
        quicksort(c, i, p-1);
        quicksort(c, p+1, f);
    }
}