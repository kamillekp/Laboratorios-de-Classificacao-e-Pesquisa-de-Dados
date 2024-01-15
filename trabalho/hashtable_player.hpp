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

        void print_player1(int id_player){
            int ind = id_player % MAX;

            cout << "sofifa_id\t" << "short_name\t" << "long_name\t\t\t" << "player_positions\t" << "rating\t" << "count\t" <<  endl;
            for(int i = 0; i < hashtable[ind].size(); i++){
                if(hashtable[ind][i].id == to_string(id_player)){
                    if(hashtable[ind][i].counts == 0){
                        cout << hashtable[ind][i].id << "\t\t" << hashtable[ind][i].short_name << "\t" << hashtable[ind][i].long_name << "\t" << hashtable[ind][i].position << "\t\t\t" << "0.0" << "\t" << hashtable[ind][i].counts << endl;
                    }
                    else{
                        float rating = hashtable[ind][i].rating / hashtable[ind][i].counts;
                        cout << hashtable[ind][i].id << "\t\t" << hashtable[ind][i].short_name << "\t" << hashtable[ind][i].long_name << "\t" << hashtable[ind][i].position << "\t\t\t" << rating << "\t" << hashtable[ind][i].counts << endl;
                    }
                    
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

        void update_rating(string id, float rating){
            int ind = stoi(id) % MAX;

            for(int i = 0; i < hashtable[ind].size(); i++){
                if(hashtable[ind][i].id == id){
                    hashtable[ind][i].update_rating(rating);
                }
            }
        }
};