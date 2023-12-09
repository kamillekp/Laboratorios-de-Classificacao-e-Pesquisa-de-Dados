#include <bits/stdc++.h>

using namespace std;

#define MAX 997
typedef struct{
    int id;
    string name;
    string position;
} Players;

Players buscaJogador (vector<vector<Players>> hashtable, int id, int *consultas);

int main(){


    //--------------------------------------------------------------------------------------------------------------------------------------
    // Declarando os dados
    //--------------------------------------------------------------------------------------------------------------------------------------

    vector<vector<Players>> hashtable(MAX);
    vector<Players> nomes;
    vector<int> consult;
    Players player;
    FILE *arq, *saida;

    int ind, ocupadas = 0, consultas;
    char linha[100];
    double tempoE, tempoP, start, end;


    //--------------------------------------------------------------------------------------------------------------------------------------
    // Lendo os dados
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("players.csv", "r");
    if(arq == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    // Adicionando os dados à hashtable
    fgets(linha, 100, arq);

    start = clock();
    while(fgets(linha, 100, arq) != NULL){
        char *token = strtok(linha, ",");
        player.id = atoi(token);

        ind = player.id % MAX;

        // contabilizando o número de posições ocupadas
        if(hashtable[ind].size() == 0){
            ocupadas++;
        }

        token = strtok(NULL, ",");
        player.name = token;

        token = strtok(NULL, ",");
        player.position = token;

        hashtable[ind].push_back(player);
    }
    end = clock();

    fclose(arq);

    // calculando o tempo de execução da inserção
    tempoE = (end - start) / (double) CLOCKS_PER_SEC;
    tempoE *= 1000;

    ocupadas = (float) ocupadas / MAX;    


    //--------------------------------------------------------------------------------------------------------------------------------------
    // Pesquisando os dados
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("consultas.csv", "r");
    if(arq == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    // Pesquisando os dados na hashtable
    start = clock();
    while(fgets(linha, 100, arq) != NULL){
        consultas = 0;
        ind = atoi(linha);

        player = buscaJogador(hashtable, ind, &consultas);

        // adicionando os dados à lista de saída
        nomes.push_back(player);
        consult.push_back(consultas);
    }
    end = clock();

    fclose(arq);

    // calculando o tempo de execução da pesquisa
    tempoP = (end - start) / (double) CLOCKS_PER_SEC;
    tempoP *= 1000;


    //--------------------------------------------------------------------------------------------------------------------------------------
    // saída do experimento
    //--------------------------------------------------------------------------------------------------------------------------------------

    saida = fopen("experimento997.txt", "w");
    if(saida == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    // printando as saídas 1
    fprintf(saida, "PARTE1: ESTATISTICAS DA TABELA HASH\n");
    fprintf(saida, "TEMPO DE CONSTRUCAO DA TABELA %lf EM MILISEGUNDOS\n", tempoE);
    fprintf(saida, "TAXA DE OCUPACAO %.2f\n", ocupadas);
    fprintf(saida, "TAMANHO MAXIMO DE LISTA #MAX1\n");      // FALTA
    fprintf(saida, "TAMANHO MEDIO DE LISTA #MED1\n");       // FALTA

    // printando as saídas 2
    fprintf(saida, "\n\nPARTE2: ESTATISTICAS DA TABELA HASH\n");
    fprintf(saida, "TEMPO DE CONSULTA %lf EM MILISEGUNDOS\n", tempoP);
    for (int i = 0; i < consult.size(); i++){
        if(nomes[i].id == -1){
            fprintf(saida, "%d NAO ENCONTRADO\n", nomes[i].id);
        }
        else{
            fprintf(saida, "%d %s %d\n", nomes[i].id, nomes[i].name.c_str(), consult[i]);
        }
    }
    fprintf(saida, "MAXIMO NUMERO DE TESTES POR NOME ENCONTRADO #MAX2\n");      // FALTA
    fprintf(saida, "MEDIA DE TESTES POR NOME ENCONTRADO #MED2\n");              // FALTA

    fclose(saida);

    return 0;
}

Players buscaJogador (vector<vector<Players>> hashtable, int id, int *consultas){
    int ind = id % 50;

    for(int i = 0; i < hashtable[ind].size(); i++){
        (*consultas)++;

        if(hashtable[ind][i].id == id){
            return hashtable[ind][i];
        }
    }

    return {ind, "", ""}; 
}
