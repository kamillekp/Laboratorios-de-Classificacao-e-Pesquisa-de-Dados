#include <bits/stdc++.h>
#include "player.hpp"
using namespace std;

void binary_insertion(vector<Player> &vet, Player player, int left, int right);

int main(){
    vector<Player> vet;

    Player p1 ("1", "Messi", "Lionel Messi", "RW", "Argentina", "FC Barcelona", "Spain Primera Division");
    Player p2 ("2", "Cristiano Ronaldo", "Cristiano Ronaldo", "ST", "Portugal", "Juventus", "Italian Serie A");
    Player p3 ("3", "Neymar Jr", "Neymar da Silva Santos Jr", "LW", "Brazil", "Paris Saint-Germain", "French Ligue 1");
    Player p4 ("4", "De Bruyne", "Kevin De Bruyne", "CAM", "Belgium", "Manchester City", "English Premier League");

    binary_insertion(vet, p1, 0, vet.size());
    binary_insertion(vet, p2, 0, vet.size());
    binary_insertion(vet, p3, 0, vet.size());
    binary_insertion(vet, p4, 0, vet.size());

    for(int i = 0; i < vet.size(); i++){
        cout << vet[i].short_name << " " << vet[i].id << endl;
    }

    return 0;
}

void binary_insertion(vector<Player> &vet, Player player, int left, int right){
    if(vet.size() == 0){
        vet.push_back(player);
        return;
    }

    int mid = (left + right) / 2;

    if(left == right){
        vet.insert(vet.begin() + mid, player);
        return;
    }

    if(player.id < vet[mid].id)
        binary_insertion(vet, player, mid+1, right);
    else
        binary_insertion(vet, player, left, mid);
}