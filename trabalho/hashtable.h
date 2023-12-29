#include <bits/stdc++.h>
#include "players.h"
using namespace std;

class Hashtable {
    private:
        vector<vector<Players>> hashtable;
        int ocupadas;
        int consultas;
        int MAX;
        
    public:
        Hashtable(int MAX){
            this->MAX = MAX;
            this->ocupadas = 0;
            this->consultas = 0;
            this->hashtable.resize(MAX);
        }

        void insereJogador (Players player){
            int ind = player.id % MAX;

            if(hashtable[ind].size() == 0){
                ocupadas++;
            }

            hashtable[ind].push_back(player);
        }

        Players buscaJogador (int id){
            int ind = id % MAX;

            for(int i = 0; i < hashtable[ind].size(); i++){
                consultas++;

                if(hashtable[ind][i].id == id){
                    return hashtable[ind][i];
                }
            }
        }

        void printa_hashtable(){
            for(int i = 0; i < MAX; i++){
                cout << i << " -> ";
                for(int j = 0; j < hashtable[i].size(); j++){
                    cout << "[" << hashtable[i][j].id << ":" << hashtable[i][j].name << ":" << hashtable[i][j].position << "] -> ";
                }
                cout << "\\" << endl;
            }
        }

        void printaPlayer(Players player){
            cout << player.id << ":" << player.name << ":" << player.position << endl;
        }

        int getOcupadas(){
            return ocupadas;
        }

        int getConsultas(){
            return consultas;
        }

        int getMAX(){
            return MAX;
        }
};