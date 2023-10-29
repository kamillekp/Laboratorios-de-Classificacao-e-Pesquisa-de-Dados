#include <bits/stdc++.h>

void shell_p2(int *vetor, int tamanho);
void shell_knuth(int *vetor, int tamanho);
void shell_ciura(int *vetor, int n);

using namespace std;

int main() {
  int tamanho_vetor;
  clock_t start, end;
  double resultado_tempo;

  while (cin >> tamanho_vetor) {
    int vetor[tamanho_vetor];
    int vetor_copia[tamanho_vetor];
  
    cout << "\nNumero de elementos na entrada: " << tamanho_vetor << endl;
    for (int i = 0; i < tamanho_vetor; i++) {
        scanf("%d", &vetor[i]);
        vetor_copia[i] = vetor[i];
    }

    /*------------------------------------------------------------------------------------------------------*/

    start = clock();
    shell_p2(vetor_copia, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);
    cout << "(SHELL P2) Tempo de execucao: " << resultado_tempo << " milissegundos" << endl;

    /*------------------------------------------------------------------------------------------------------*/

    for (int i = 0; i < tamanho_vetor; i++) {
      vetor_copia[i] = vetor[i];
    }

    start = clock();
    shell_knuth(vetor_copia, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);
    cout << "(SHELL KNUTH) Tempo de execucao: " << resultado_tempo << " milissegundos" << endl;
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

// SHELL CIURA
void shell_ciura(int *vetor, int n){
  int vet_seq[17] = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};
  int num_inicial = 16;
  int aux, j, h;

  for(int i = 0; i < 17; i++){
    if(vet_seq[i] > n){
        h = vet_seq[i-1];
        break;
    }
  }

  while(h > 0){
    for(int i = h; i < n; i++) {
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