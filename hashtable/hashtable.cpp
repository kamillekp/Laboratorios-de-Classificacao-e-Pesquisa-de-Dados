#include <bits/stdc++.h>

using namespace std;

#define MAX 997 // fixo para criar os testes M = 997, 1999, 3989 e 7993
typedef struct{
    int id;
    string name;
    string position;
} Players;

void insereJogador (vector<vector<Players>>& hashtable, Players player, int *ocupadas);
Players buscaJogador (vector<vector<Players>>& hashtable, int id, int *consultas);
void printa_hashtable(vector<vector<Players>>& hashtable,int numLinhas);
void printaPlayer(Players player);

int main(){

    
    //--------------------------------------------------------------------------------------------------------------------------------------
    // Declarando os dados
    //--------------------------------------------------------------------------------------------------------------------------------------

    vector<vector<Players>> hashtable(MAX);
    vector<Players> nomes;
    Players player;
    vector<int> consult;
    FILE *arq, *saida;

    int id, ocupadas = 0, consultas;
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
        
        token = strtok(NULL, ",");
        player.name = token;

        token = strtok(NULL, "\"");
        player.position = token;

        insereJogador(hashtable, player, &ocupadas);
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
        id = atoi(linha);

        player = buscaJogador(hashtable, id, &consultas);

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

    //printando as saídas 2
    fprintf(saida, "\n\nPARTE2:  ESTATISTICAS DAS CONSULTAS\n");
    fprintf(saida, "TEMPO DE CONSULTA %lf EM MILISEGUNDOS\n", tempoP);
    for (int i = 0; i < consult.size(); i++){
        fprintf(saida, "%d %s %d\n", nomes[i].id, nomes[i].name.c_str(), consult[i]);
    }
    fprintf(saida, "MAXIMO NUMERO DE TESTES POR NOME ENCONTRADO #MAX2\n");      // FALTA
    fprintf(saida, "MEDIA DE TESTES POR NOME ENCONTRADO #MED2\n");              // FALTA

    fclose(saida);

    return 0;
}

void insereJogador (vector<vector<Players>>& hashtable, Players player, int *ocupadas){
    int ind = player.id % MAX;

    if(hashtable[ind].size() == 0){
        (*ocupadas)++;
    }

    hashtable[ind].push_back(player); // esta acontecendo o push_back
}

Players buscaJogador (vector<vector<Players>>& hashtable, int id, int *consultas){
    int ind = id % MAX;

    for(int i = 0; i < hashtable[ind].size(); i++){
        (*consultas)++;

        if(hashtable[ind][i].id == id){
            return hashtable[ind][i];
        }
    }

    Players playerNotFound;

    playerNotFound.id = id;
    playerNotFound.name = "NAO ENCONTRADO";
    playerNotFound.position = "";

    return playerNotFound; 
}

void printa_hashtable(vector<vector<Players>>& hashtable, int numLinhas){
    for(int i =0; i < numLinhas; i++){
        cout << i << " ";
        for(int j = 0; j < hashtable[i].size(); j++){
            cout << hashtable[i][j].id << " ";
        }
        cout << endl;
    }
}

void printaPlayer(Players player){
    cout << player.id << " " << player.name << " " << player.position << endl;
}