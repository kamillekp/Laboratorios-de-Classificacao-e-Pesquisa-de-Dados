#include <bits/stdc++.h>
#include "user.hpp"
using namespace std;

class Hashtable_User {
    private:
        vector<vector<User>> hashtable;
        int ocupadas;
        int consultas;
        int MAX;
        
    public:
        Hashtable_User(int MAX){
            this->MAX = MAX;
            this->ocupadas = 0;
            this->consultas = 0;
            this->hashtable.resize(MAX);
        }

        void insert_user (User user){
            int ind = stoi(user.id) % MAX;

            if(hashtable[ind].size() == 0){
                ocupadas++;
            }

            hashtable[ind].push_back(user);
        }

        User find_user (string id){
            int ind = stoi(id) % MAX;

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
                    cout << "[" << hashtable[i][j].id << ":" << hashtable[i][j].id_player << ":" << hashtable[i][j].rate << "] -> ";
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