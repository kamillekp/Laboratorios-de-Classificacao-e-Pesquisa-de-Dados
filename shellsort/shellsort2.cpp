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

    cout << "\nSEQ SHELL P2, " << resultado_tempo << " milissegundos, " << "2.40GHz 11th Gen Intel Core i5" << endl;

    /*------------------------------------------------------------------------------------------------------*/

    for (int i = 0; i < tamanho_vetor; i++) {
      vetor_copia[i] = vetor[i];
    }

    start = clock();
    shell_knuth(vetor_copia, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);

    cout << "SEQ SHELL KNUTH, " << resultado_tempo << " milissegundos" << "2.40GHz 11th Gen Intel Core i5" << endl;

    /*------------------------------------------------------------------------------------------------------*/

    for (int i = 0; i < tamanho_vetor; i++) {
      vetor_copia[i] = vetor[i];
    }

    start = clock();
    shell_ciura(vetor_copia, tamanho_vetor);
    end = clock();

    resultado_tempo = (double) (end - start);

    cout << "SEQ SHELL CIURA, " << resultado_tempo << " milissegundos" << "2.40GHz 11th Gen Intel Core i5" << endl;

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
  }
}

// SHELL CIURA
void shell_ciura(int *vetor, int tamanho){
  int vet_seq[18] = {0,1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};
  int num_inicial = 17;

  for(int i = 0; i < 18; i++){
    if(vet_seq[i] > tamanho){
        num_inicial = i-1;
        break;
    }
  }

  while(vet_seq[num_inicial] > 0) {   
    for(int i = vet_seq[num_inicial]; i < tamanho; i++) {
      int j = i;

      while (j >= vet_seq[num_inicial] && vetor[j] < vetor[j - vet_seq[num_inicial]]) {
        int temp = vetor[j];
        vetor[j] = vetor[j - vet_seq[num_inicial]];
        vetor[j - vet_seq[num_inicial]] = temp;
        j -= vet_seq[num_inicial];
      }
    }
    
    num_inicial--;
  }
}