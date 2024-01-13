#include <bits/stdc++.h>
#include "player.hpp"
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
            int ind = stoi(player.id) % MAX;

            if(hashtable[ind].size() == 0){
                ocupadas++;
            }

            hashtable[ind].push_back(player);
        }

        Player find_player (string id){
            int ind = stoi(id) % MAX;

            for(int i = 0; i < hashtable[ind].size(); i++){
                consultas++;

                if(hashtable[ind][i].id == id){
                    return hashtable[ind][i];
                }
            }
        }

        void print_player(int id_player){
            int ind = id_player % MAX;

            for(int i = 0; i < hashtable[ind].size(); i++){
                if(hashtable[ind][i].id == to_string(id_player)){
                    cout << hashtable[ind][i].id << ":" << hashtable[ind][i].short_name << ":" << hashtable[ind][i].long_name << ":" << hashtable[ind][i].position << ":" << hashtable[ind][i].nacionality << ":" << hashtable[ind][i].club << ":" << hashtable[ind][i].league << endl;
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