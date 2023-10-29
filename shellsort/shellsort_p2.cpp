#include <bits/stdc++.h>
void shell_p2(int *vetor, int tamanho);

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
    shell_p2(vetor, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);
    cout << "(SHELL P2) Tempo de execucao: " << resultado_tempo << " milissegundos" << endl;
  }
}

// SHELL POTÊNCIAS DE DOIS
void shell_p2(int *vetor, int tamanho) {
  int h = tamanho / 2;

  while (h >= 1) {
    for (int i = h; i < tamanho; i++) {
      int j = i;

      while (j >= h && vetor[j] < vetor[j - h]) {
        int temp = vetor[j];
        vetor[j] = vetor[j - h];
        vetor[j - h] = temp;
        j -= h;
      }
    }

    h /= 2;
  }
}