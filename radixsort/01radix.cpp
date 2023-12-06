#include <bits/stdc++.h>
using namespace std;

char vet[10000000];

typedef struct {
    string palavra;
    int frequencia;
} Palavra;

int charAt(string s, int d);
void radixSortMSD(vector<string>& arr, int low, int high, int d);
void radixSort(vector<string>& arr, int size);

int main() {
    vector<Palavra> palavras;
    vector<string> textoF, textoW;
    FILE *arq;
    char *token;
    int size;


    //--------------------------------------------------------------------------------------------------------------------------------------
    // FRANKESTEIN_SORTED
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("frankestein.txt", "r");

    // verifica se houve erro na abertura ou não
    if(!arq){
        cout << "Erro na abertura.";
        return 0;
    }

    // pega no vetor vet a string completa do arquivo
    fgets(vet, sizeof(vet), arq);

    // divide as palavras do texto por " "
    token = strtok(vet, " ");
    while(token != NULL) {
        textoF.push_back(token);     // passa a palavra separada por " " da vez para o vector string texto
        token = strtok(NULL, " ");
    }

    size = textoF.size();

    // Ordenando as strings
    radixSort(textoF, size);
    fclose(arq);

    arq = fopen("frankenstein_sorted.txt", "w");

    for (const string& s : textoF) {
        fputs(s.c_str(), arq);
        fputs("\n", arq);
    }

    fclose(arq);


    //--------------------------------------------------------------------------------------------------------------------------------------
    // WAR_AND_PEACE_SORTED
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("war_and_peace.txt", "r");

    // verifica se houve erro na abertura ou não
    if(!arq){
        cout << "Erro na abertura.";
        return 0;
    }

    // pega no vetor vet a string completa do arquivo
    fgets(vet, sizeof(vet), arq);

    // divide as palavras do texto por " "
    token = strtok(vet, " ");
    while(token != NULL) {
        textoW.push_back(token);     // passa a palavra separada por " " da vez para o vector string texto
        token = strtok(NULL, " ");
    }

    size = textoW.size();

    // Ordenando as strings
    radixSort(textoW, size);
    fclose(arq);

    arq = fopen("war_and_peace_sorted.txt", "w");

    for (const string& s : textoW) {
        fputs(s.c_str(), arq);
        fputs("\n", arq);
    }

    fclose(arq);


    //--------------------------------------------------------------------------------------------------------------------------------------
    // FRANKESTEIN_COUNTED
    //--------------------------------------------------------------------------------------------------------------------------------------
    arq = fopen("frankestein_counted.txt", "w");

    // verifica se houve erro na abertura ou não
    if(!arq){
        cout << "Erro na abertura.";
        return 0;
    }   

    for(int i = 0; i < textoF.size(); i++) {
        int count = 1;
        while(textoF[i] == textoF[i+1]) {
            count++;
            i++;
        }
        
        string str = textoF[i] + " " + to_string(count) + "\n";
        fputs(str.c_str(), arq);
    }

    fclose(arq);


    //--------------------------------------------------------------------------------------------------------------------------------------
    // WAR_AND_PEACE_COUNTED
    //--------------------------------------------------------------------------------------------------------------------------------------
    arq = fopen("war_and_peace_counted.txt", "w");

    // verifica se houve erro na abertura ou não
    if(!arq){
        cout << "Erro na abertura.";
        return 0;
    }   

    for(int i = 0; i < textoW.size(); i++) {
        int count = 1;
        while(textoW[i] == textoW[i+1]) {
            count++;
            i++;
        }
        
        string str = textoW[i] + " " + to_string(count) + "\n";
        fputs(str.c_str(), arq);
    }

    fclose(arq);


    //--------------------------------------------------------------------------------------------------------------------------------------
    // FRANKESTEIN_RANKED
    //--------------------------------------------------------------------------------------------------------------------------------------
    
    arq = fopen("frankestein_counted.txt", "r");

    if(!arq){
        cout << "Erro na abertura.";
        return 0;
    }

    // pega no vetor palavras linha por llinha do arquivo 
    while(fgets(vet, sizeof(vet), arq) != NULL) {
        Palavra p;
        string str = vet;

        int pos = str.find(" ");

        p.palavra = str.substr(0, pos);
        p.frequencia = stoi(str.substr(pos+1, str.length()-1));

        palavras.push_back(p);
    }

    // ordena o vetor de palavras por frequencia decrescente
    sort(palavras.begin(), palavras.end(), [](Palavra a, Palavra b) {
        return a.frequencia > b.frequencia;
    });

    fclose(arq);
    
    // escreve no arquivo frankenstein_ranked.txt as palavras e suas frequencias
    arq = fopen("frankestein_ranked.txt", "w");

    for(int i = 0; i < 1000; i++) {
        string str = palavras[i].palavra + " " + to_string(palavras[i].frequencia) + "\n";
        fputs(str.c_str(), arq);
    }

    fclose(arq);
    palavras.clear();


    //--------------------------------------------------------------------------------------------------------------------------------------
    // WAR_AND_PEACE_RANKED
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("war_and_peace_counted.txt", "r");

    if(!arq){
        cout << "Erro na abertura.";
        return 0;
    }

    // pega no vetor palavras linha por llinha do arquivo 
    while(fgets(vet, sizeof(vet), arq) != NULL) {
        Palavra p;
        string str = vet;

        int pos = str.find(" ");

        p.palavra = str.substr(0, pos);
        p.frequencia = stoi(str.substr(pos+1, str.length()-1));

        palavras.push_back(p);
    }

    // ordena o vetor de palavras por frequencia decrescente
    sort(palavras.begin(), palavras.end(), [](Palavra a, Palavra b) {
        return a.frequencia > b.frequencia;
    });

    fclose(arq);
    
    // escreve no arquivo frankenstein_ranked.txt as palavras e suas frequencias
    arq = fopen("war_and_peace_ranked.txt", "w");

    for(int i = 0; i < 1000; i++) {
        string str = palavras[i].palavra + " " + to_string(palavras[i].frequencia) + "\n";
        fputs(str.c_str(), arq);
    }

    fclose(arq);


    return 0;
}


// Função para obter o caractere na posição d da string
int charAt(string s, int d) {
    if (d < s.length()) {
        return s[d];
    }
    return -1;
}

// Função para realizar o Radix Sort MSD recursivo
void radixSortMSD(vector<string>& arr, int low, int high, int d) {
    const int R = 256; // ASCII
    if (high <= low || d < 0) {
        return;
    }

    // Array para contar a frequência dos caracteres
    vector<int> count(R + 2, 0);

    // Contagem dos caracteres na posição d
    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        count[c + 2]++;
    }

    // Transformando a contagem em índices
    for (int r = 0; r < R + 1; ++r) {
        count[r + 1] += count[r];
    }

    // Ordenando os elementos baseado no caractere na posição d
    vector<string> aux(high - low + 1);
    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]++] = arr[i];
    }

    // Copiando de volta para o vetor original
    for (int i = low; i <= high; ++i) {
        arr[i] = aux[i - low];
    }

    // Chamando recursivamente para cada caractere
    for (int r = 0; r < R; ++r) {
        radixSortMSD(arr, low + count[r], low + count[r + 1] - 1, d + 1);
    }
}

// Função de ordenação Radix Sort MSD
void radixSort(vector<string>& arr, int size) {
    radixSortMSD(arr, 0, size - 1, 0);
}


// ordenar o conteudo de frankestein_counted.txt por frequencia descrescentemente


// ordenar o conteudo de war_and_peace_counted.txt por frequencia descrescentemente