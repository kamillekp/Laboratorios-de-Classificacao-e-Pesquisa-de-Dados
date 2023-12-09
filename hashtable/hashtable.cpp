#include <bits/stdc++.h>

using namespace std;
typedef struct{
    int id;
    string name;
    string position;
} Players;

void buscaJogador (vector<vector<Players>> hashtable, int id);

int main(){
    // Declarando os dados
    vector<vector<Players>> hashtable(50);
    Players player;
    FILE *arq;

    char linha[100];
    int ind;


    //--------------------------------------------------------------------------------------------------------------------------------------
    // Lendo os dados
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("playerscopy.csv", "r");

    if(arq == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    // Adicionando os dados à hashtable
    fgets(linha, 100, arq);
    while(fgets(linha, 100, arq) != NULL){
        char *token = strtok(linha, ",");
        player.id = atoi(token);

        ind = player.id % 50;

        token = strtok(NULL, ",");
        player.name = token;

        token = strtok(NULL, ",");
        player.position = token;

        hashtable[ind].push_back(player);
    }

    fclose(arq);


    //--------------------------------------------------------------------------------------------------------------------------------------
    // Pesquisando os dados
    //--------------------------------------------------------------------------------------------------------------------------------------

    arq = fopen("consultascopy.csv", "r");

    if(arq == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    while(fgets(linha, 100, arq) != NULL){
        ind = atoi(linha);
        buscaJogador(hashtable, ind);
    }

    return 0;
}

void buscaJogador (vector<vector<Players>> hashtable, int id){
    int ind = id % 50;
    int flag = 0;

    for(int i = 0; i < hashtable[ind].size(); i++){
        if(hashtable[ind][i].id == id){
            cout << "Nome do jogador: " << hashtable[ind][i].name << endl;
            flag = 1;
            break;
        }
    }

    if(flag == 0){
        cout << "Jogador nao encontrado" << endl;
    }

}
