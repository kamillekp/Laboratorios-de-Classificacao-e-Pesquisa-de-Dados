#include <bits/stdc++.h>

//PELO PROMPT
// g++ 'nomeProg.cpp' -o A (gera executavel)
// .\a.exe < entrada.txt
// .\a.exe < entrada.txt > saida.txt

void shell_p2(int *vetor, int tamanho);
void shell_knuth(int *vetor, int n);

using namespace std;

int main() {
  int tamanho_vetor;

    while (cin >> tamanho_vetor) {
        int vetor[tamanho_vetor];

        cout << "\nNumero de elementos na entrada: " << tamanho_vetor << "\n Vars: ";
        for (int i = 0; i < tamanho_vetor; i++) {
            scanf("%d", &vetor[i]);
            cout << vetor[i] << "\t";
        }

        shell_p2(vetor, tamanho_vetor);

        cout << "\nOrganizado: ";
        for (int i = 0; i < tamanho_vetor; i++) {
            cout << vetor[i] << "\t";
        }

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