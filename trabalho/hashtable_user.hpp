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

        void binary_insertion(vector<User> &vet, User user, int left, int right){
            if(vet.size() == 0){
                vet.push_back(user);
                return;
            }

            int mid = (left + right) / 2;

            if(left == right){
                vet.insert(vet.begin() + mid, user);
                return;
            }

            if(user.rate < vet[mid].rate)
                binary_insertion(vet, user, mid+1, right);
            else
                binary_insertion(vet, user, left, mid);
        }

        vector<User> find_user_ratings (string id){
            int ind = stoi(id) % MAX;
            vector<User> vet;

            for(int i = 0; i < hashtable[ind].size(); i++){
                if(hashtable[ind][i].id == id){
                    binary_insertion(vet, hashtable[ind][i], 0, vet.size());
                }
            }

            return vet;
        }
        
        void printa_users(vector<User> &vet){
            for(int i = 0; i < vet.size(); i++){
                cout << vet[i].id_player << " " << vet[i].rate << endl;
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