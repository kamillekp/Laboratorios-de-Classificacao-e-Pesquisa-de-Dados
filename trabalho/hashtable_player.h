#include <bits/stdc++.h>
#include "player.h"
using namespace std;

class Hashtable_Player {
    private:
        vector<vector<Player>> hashtable;
        int ocupadas;
        int consultas;
        int MAX;
        
    public:
        Hashtable_Player(int MAX){
            this->MAX = MAX;
            this->ocupadas = 0;
            this->consultas = 0;
            this->hashtable.resize(MAX);
        }

        void insert_player (Player player){
            int ind = player.id % MAX;

            if(hashtable[ind].size() == 0){
                ocupadas++;
            }

            hashtable[ind].push_back(player);
        }

        Player find_player (int id){
            int ind = id % MAX;

            for(int i = 0; i < hashtable[ind].size(); i++){
                consultas++;

                if(hashtable[ind][i].id == id){
                    return hashtable[ind][i];
                }
            }
        }

        void print_hashtable(){
            for(int i = 0; i < MAX; i++){
                cout << i << " -> ";
                for(int j = 0; j < hashtable[i].size(); j++){
                    cout << "[" << hashtable[i][j].id << ":" << hashtable[i][j].short_name << ":" << hashtable[i][j].long_name << ":" << hashtable[i][j].position << ":" << hashtable[i][j].nacionality << ":" << hashtable[i][j].club << ":" << hashtable[i][j].league << "] -> ";
                }
                cout << "\\" << endl;
            }
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