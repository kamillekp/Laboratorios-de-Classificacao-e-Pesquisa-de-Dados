#include <bits/stdc++.h>

using namespace std;

typedef struct{
    int id;
    string team;
    string position;
} Players;

int main(){
    vector<vector<Players>> hashtable(50);
    Players player;
    FILE *arq;
    int ind;

    arq = fopen("playerscopy.csv", "r");

    if(arq == NULL){
        cout << "Erro ao abrir o arquivo" << endl;
        return 0;
    }

    char linha[1000];
    fgets(linha, 1000, arq);

    while(fgets(linha, 1000, arq) != NULL){
        char *token = strtok(linha, ",");
        player.id = atoi(token);

        ind = player.id % 50;

        token = strtok(NULL, ",");
        player.team = token;

        token = strtok(NULL, ",");
        player.position = token;

        hashtable[ind].push_back(player);
    }

    fclose(arq);

    for(int i = 0; i < 100; i++){
        cout << "Indice: " << i << endl;
        for(int j = 0; j < hashtable[i].size(); j++){
            cout << hashtable[i][j].id << " " << hashtable[i][j].team << " " << hashtable[i][j].position << endl;
        }
    }

    return 0;
}

