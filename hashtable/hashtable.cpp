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
    int ind, indPesquisa;

    // Lidando com o arquivo
    arq = fopen("playerscopy.csv", "r");

    if(arq == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    char linha[100];
    fgets(linha, 100, arq);

    // Adicionando os dados à hashtable
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

    // Pesquisando os dados
    do{
        cout << "Digite o id do jogador (-1 para parar): ";
        cin >> indPesquisa;

        buscaJogador(hashtable, indPesquisa);
    }while(ind != -1);

    return 0;
}

void buscaJogador (vector<vector<Players>> hashtable, int id){
    int ind = id % 50;

    for(int i = 0; i < hashtable[ind].size(); i++){
        if(hashtable[ind][i].id == id){
            cout << "Nome do jogador: " << hashtable[ind][i].name << endl;
            break;
        }
    }
}
