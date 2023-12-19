#include <bits/stdc++.h>

using namespace std;
typedef struct{
    int id;
    string name;
    string position;
} Players;

void insereJogador (vector<vector<Players>>& hashtable, Players player, int *ocupadas, int MAX);
Players buscaJogador (vector<vector<Players>>& hashtable, int id, int *consultas, int MAX);
void printa_hashtable(vector<vector<Players>>& hashtable,int numLinhas);
void printaPlayer(Players player);

int main(int argc, char *argv[]){

    
    //--------------------------------------------------------------------------------------------------------------------------------------
    // Declarando os dados
    //--------------------------------------------------------------------------------------------------------------------------------------
    int MAX = atoi(argv[1]);

    vector<vector<Players>> hashtable(MAX);
    vector<Players> nomes;
    Players player;
    vector<int> consult;
    FILE *arq, *saida;

    int id, ocupadas = 0, consultas, flagConsulta = 0, start, end, maiorConsulta;
    float mediaConsultas, taxaOcup;
    char linha[100];
    double tempoE, tempoP;


    //--------------------------------------------------------------------------------------------------------------------------------------
    // Lendo os dados
    //--------------------------------------------------------------------------------------------------------------------------------------
    
    arq = fopen(argv[2], "r"); 
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

        insereJogador(hashtable, player, &ocupadas, MAX);
    }
    end = clock();

    fclose(arq);

    // calculando o tempo de execução da inserção
    tempoE = (double) (end - start) / CLOCKS_PER_SEC;
    tempoE *= 1000;

    // taxa de ocupação da hashtable
    taxaOcup = (float) ocupadas / MAX;

    int max=hashtable[0].size();
    int sum=0,media=0;
    for(int i=0;i<hashtable.size();i++){
        if(hashtable[i].size()>max){
            max=hashtable[i].size();
        }
        sum+=hashtable[i].size();
    }
    media=sum/hashtable.size();

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

        player = buscaJogador(hashtable, id, &consultas, MAX);

        if(flagConsulta == 0){
            maiorConsulta = consultas;
            flagConsulta = 1;
        }
        else if(consultas > maiorConsulta){
            maiorConsulta = consultas;
        }

        // adicionando os dados à lista de saída
        nomes.push_back(player);
        consult.push_back(consultas);
    }
    end = clock();

    fclose(arq);

    // calculando a média de consultas
    for(int i = 0; i < consult.size(); i++){
        mediaConsultas += consult[i];
    }
    mediaConsultas = mediaConsultas / (float) consult.size();

    // calculando o tempo de execução da pesquisa
    tempoP = (double) (end - start) / CLOCKS_PER_SEC;
    tempoP *= 1000;


    //--------------------------------------------------------------------------------------------------------------------------------------
    // saída do experimento
    //--------------------------------------------------------------------------------------------------------------------------------------

    char nomeArq[100];
    strcpy(nomeArq, argv[1]);
    strcat(nomeArq, ".txt");

    saida = fopen(nomeArq, "w");
    if(saida == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    // printando as saídas 1
    fprintf(saida, "PARTE1: ESTATISTICAS DA TABELA HASH\n");
    fprintf(saida, "TEMPO DE CONSTRUCAO DA TABELA %.0f MILISEGUNDOS\n", tempoE);
    fprintf(saida, "TAXA DE OCUPACAO %.2f \n", taxaOcup*100);
    fprintf(saida, "TAMANHO MAXIMO DE LISTA %d\n",max);      // FALTA
    fprintf(saida, "TAMANHO MEDIO DE LISTA %d\n",media);       // FALTA

    //printando as saídas 2
    fprintf(saida, "\n\nPARTE2:  ESTATISTICAS DAS CONSULTAS\n");
    fprintf(saida, "TEMPO DE CONSULTA %.0f EM MILISEGUNDOS\n", tempoP);
    for (int i = 0; i < consult.size(); i++){
        fprintf(saida, "%d %s %d\n", nomes[i].id, nomes[i].name.c_str(), consult[i]);
    }
    fprintf(saida, "MAXIMO NUMERO DE TESTES POR NOME ENCONTRADO %d\n", maiorConsulta);
    fprintf(saida, "MEDIA DE TESTES POR NOME ENCONTRADO %d\n", mediaConsultas);     

    fclose(saida);

    return 0;
}

void insereJogador (vector<vector<Players>>& hashtable, Players player, int *ocupadas, int MAX){
    int ind = player.id % MAX;

    if(hashtable[ind].size() == 0){
        (*ocupadas)++;
    }

    hashtable[ind].push_back(player); // esta acontecendo o push_back
}

Players buscaJogador (vector<vector<Players>>& hashtable, int id, int *consultas, int MAX){
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