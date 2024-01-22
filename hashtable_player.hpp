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

        void insert_player (Player player);
        Player find_player (string id);
        void print_player1(int id_player);          // PESQUISA 1
        void print_player3(int id_player);          // PESQUISA 3
        void print_player4(int id_player);          // PESQUISA 4
        void print_hashtable();                     // APAGAR DEPOIS
        void update_rating(string id, float rating);
        void binary_insertion(vector<Player> &vet, Player player, int left, int right);
        vector<Player> find_players_by_position(string position);
};

void Hashtable_Player::insert_player (Player player){
    int ind = stoi(player.id) % MAX;

    if(hashtable[ind].size() == 0){
        ocupadas++;
    }

    hashtable[ind].push_back(player);
}

Player Hashtable_Player::find_player (string id){
    int ind = stoi(id) % MAX;

    for(int i = 0; i < hashtable[ind].size(); i++){
        consultas++;

        if(hashtable[ind][i].id == id){
            return hashtable[ind][i];
        }
    }
}

void Hashtable_Player::print_player1(int id_player){
    int ind = id_player % MAX;

    for(int i = 0; i < hashtable[ind].size(); i++){
        if(hashtable[ind][i].id == to_string(id_player)){
            if(hashtable[ind][i].counts == 0){
                cout << "1) " << hashtable[ind][i].id << ", 2) " << hashtable[ind][i].short_name << ", 3) " << hashtable[ind][i].long_name << ", 4) " << hashtable[ind][i].position << ", 5) " << "0.0" << ", 6) " << hashtable[ind][i].counts << endl;
            }
            else{
                float rating = hashtable[ind][i].rating / hashtable[ind][i].counts;
                cout << "1) " << hashtable[ind][i].id << ", 2) " << hashtable[ind][i].short_name << ", 3) " << hashtable[ind][i].long_name << ", 4) " << hashtable[ind][i].position << ", 5) " << rating << ", 6) " << hashtable[ind][i].counts << endl;
            }
            
        }
    }
}

void Hashtable_Player::print_player4(int id_player){
    int ind = id_player % MAX;

    for(int i = 0; i < hashtable[ind].size(); i++){
        if(hashtable[ind][i].id == to_string(id_player)){
            if(hashtable[ind][i].counts == 0){
                cout << "1) " << hashtable[ind][i].id << ", 2) " << hashtable[ind][i].short_name << ", 3) " << hashtable[ind][i].long_name << ", 4) " << hashtable[ind][i].nacionality << ", 5) " << hashtable[ind][i].club << ", 6) " << hashtable[ind][i].league << ", 7) " << fixed << setprecision(6) << hashtable[ind][i].rate << ", 8) " << setprecision(0) << hashtable[ind][i].counts << endl;
            }
            else{
                float rating = hashtable[ind][i].rating / hashtable[ind][i].counts;
                cout << "1) " << hashtable[ind][i].id << ", 2) " << hashtable[ind][i].short_name << ", 3) " << hashtable[ind][i].long_name << ", 4) " << hashtable[ind][i].nacionality << ", 5) " << hashtable[ind][i].club << ", 6) " << hashtable[ind][i].league << ", 7) " << fixed << setprecision(6) << hashtable[ind][i].rate << ", 8) " << setprecision(0) << hashtable[ind][i].counts << endl;
            }
            
        }
    }
}

void Hashtable_Player::update_rating(string id, float rating){
    int ind = stoi(id) % MAX;

    for(int i = 0; i < hashtable[ind].size(); i++){
        if(hashtable[ind][i].id == id){
            hashtable[ind][i].update_rating(rating);
        }
    }
}

void Hashtable_Player::print_hashtable(){
    for(int i = 0; i < MAX; i++){
        cout << i << " -> ";
        for(int j = 0; j < hashtable[i].size(); j++){
            cout << "[" << hashtable[i][j].id << ":" << hashtable[i][j].short_name << ":" << hashtable[i][j].long_name << ":" << hashtable[i][j].position << ":" << hashtable[i][j].nacionality << ":" << hashtable[i][j].club << ":" << hashtable[i][j].league << "] -> ";
        }
        cout << "\\" << endl;
    }
}

void Hashtable_Player::binary_insertion(vector<Player> &vet, Player player, int left, int right){
    if(vet.size() == 0){
        vet.push_back(player);
        return;
    }

    int mid = (left + right) / 2;

    if(left == right){
        vet.insert(vet.begin() + mid, player);
        return;
    }

    if(player.rate < vet[mid].rate)
        binary_insertion(vet, player, mid+1, right);
    else
        binary_insertion(vet, player, left, mid);
}

vector<Player> Hashtable_Player::find_players_by_position(string position){
    vector<Player> players;

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < hashtable[i].size(); j++){
            if(hashtable[i][j].position.find(position) != string::npos){
                players.push_back(hashtable[i][j]);
            }
        }
    }

    return players;
}