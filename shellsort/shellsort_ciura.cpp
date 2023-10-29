#include <bits/stdc++.h>
void shell_ciura(int *vetor, int n);

using namespace std;

int main() {
  int tamanho_vetor;
  clock_t start, end;
  double resultado_tempo;

  while (cin >> tamanho_vetor) {
    int vetor[tamanho_vetor];

    cout << "\nNumero de elementos na entrada: " << tamanho_vetor << endl;
    for (int i = 0; i < tamanho_vetor; i++) {
        scanf("%d", &vetor[i]);
    }

    start = clock();
    shell_ciura(vetor, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);
    cout << "(SHELL CIURA) Tempo de execucao: " << resultado_tempo << " milissegundos" << endl;

    for (int i = 0; i < tamanho_vetor; i++) {
        cout << vetor[i] << "\t";
    }

  }
}

// SHELL CIURA
void shell_ciura(int *vetor, int n){
    int vet_seq[17] = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};
    int num_inicial = 16;
    int aux, i, j;

    for(int i = 0; i < 17; i++){
        if(vet_seq[i] > n){
            num_inicial = i-1;
            break;
        }
    }

    int h = vet_seq[num_inicial];    

    while(h > 0){
        for(i = h; i < n; i++) {
            aux = vetor[i];
            j = i;

            /* efetua comparações entre elementos com distância h: */
            while(vetor[j - h] > aux) {
                vetor[j] = vetor[j - h];
                j -= h;
                if(j < h) break;
            }

            vetor[j] = aux;
        }

        num_inicial--;
        h = vet_seq[num_inicial];
    }
}