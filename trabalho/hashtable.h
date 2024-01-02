#include <bits/stdc++.h>
#include "players.h"
#include "user.h"
using namespace std;

class Hashtable {
    private:
        vector<vector<Players>> hashtable;
        vector<vector<User>> hashtable_user;
        int ocupadas;
        int consultas;
        int MAX;
        
    public:
        Hashtable(int MAX, int selection){
            this->MAX = MAX;
            this->ocupadas = 0;
            this->consultas = 0;

            if(selection == 0)
                this->hashtable.resize(MAX);
            else if(selection == 1)
                this->hashtable_user.resize(MAX);
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
                    cout << "[" << hashtable[i][j].id << ":" << hashtable[i][j].short_name << ":" << hashtable[i][j].long_name << ":" << hashtable[i][j].position << ":" << hashtable[i][j].nacionality << ":" << hashtable[i][j].club << ":" << hashtable[i][j].league << "] -> ";
                }
                cout << "\\" << endl;
            }
        }

        void printaPlayer(Players player){
            cout << player.id << ":" << player.long_name << ":" << player.position << endl;
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