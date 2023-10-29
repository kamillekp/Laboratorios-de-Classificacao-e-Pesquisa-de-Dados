#include <bits/stdc++.h>
void shell_knuth(int *vetor, int n);

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
    shell_knuth(vetor, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);
    cout << "(SHELL KNUTH) Tempo de execucao: " << resultado_tempo << " milissegundos" << endl;
  }
}

// SHELL KNUTH
void shell_knuth(int *vetor, int tamanho) {
    int i, j, h;
    int aux;

    for(h = 1; h < tamanho; h = 3*h+1); /* calcula o h inicial. */

    while(h > 0) {
        h = (h-1)/3; /* atualiza o valor de h. */
        for(i = h; i < tamanho; i++) {
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
    }
}