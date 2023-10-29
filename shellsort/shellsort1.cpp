#include <bits/stdc++.h>

void shell_p2(int *vetor, int tamanho);
void shell_knuth(int *vetor, int tamanho);
void shell_ciura(int *vetor, int n);

using namespace std;

int main() {
  int tamanho_vetor;

  while (cin >> tamanho_vetor) {
    int vetor[tamanho_vetor];
    int vetor_copia[tamanho_vetor];
  
    cout << "\nNumero de elementos na entrada: " << tamanho_vetor << endl;
    for (int i = 0; i < tamanho_vetor; i++) {
        scanf("%d", &vetor[i]);
        vetor_copia[i] = vetor[i];
    }

    /*------------------------------------------------------------------------------------------------------*/

    cout << "\nSEQ SHELL P2" << endl;
    shell_p2(vetor_copia, tamanho_vetor);

    /*------------------------------------------------------------------------------------------------------*/

    for (int i = 0; i < tamanho_vetor; i++) {
      vetor_copia[i] = vetor[i];
    }

    cout << "SEQ SHELL KNUTH" << endl;
    shell_knuth(vetor_copia, tamanho_vetor);

    /*------------------------------------------------------------------------------------------------------*/

    cout << "\n";
  }
}

// SHELL POTÊNCIAS DE DOIS
void shell_p2(int *vetor, int tamanho) {
  int h;

  for(h = 1; h < tamanho/2; h = h*2);   

  while (h > 0) {
    for (int i = h; i < tamanho; i++) {
      int j = i;

      while (j >= h && vetor[j] < vetor[j - h]) {
        int temp = vetor[j];
        vetor[j] = vetor[j - h];
        vetor[j - h] = temp;
        j -= h;
      }
    }

    for(int j = 0; j < tamanho; j++){
      cout << vetor[j] << " ";
    }
    cout << "INCR = " << h << endl;

    h /= 2;
  }
}

// SHELL KNUTH
void shell_knuth(int *vetor, int tamanho) {
  int h;
  
  for(h = 1; h < tamanho; (h = (3 * h) + 1)); 

  while(h > 0) {
    h = (h-1)/3;
    
    for(int i = h; i < tamanho; i++) {
      int j = i;

      while (j >= h && vetor[j] < vetor[j - h]) {
        int temp = vetor[j];
        vetor[j] = vetor[j - h];
        vetor[j - h] = temp;
        j -= h;
      }
    }

    for(int j = 0; j < tamanho; j++){
      cout << vetor[j] << " ";
    }
    cout << "INCR = " << h << endl;
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