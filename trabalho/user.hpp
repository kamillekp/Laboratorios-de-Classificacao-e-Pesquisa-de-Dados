#include <bits/stdc++.h>
using namespace std;

class User {
    public:
        string id;
        string id_player;
        string rate;

        User(string id, string id_player, string rate){
            this->id = id;
            this->id_player = id_player;
            this->rate = rate;
        }
};



/*#include <bits/stdc++.h>
#include "player.hpp"

using namespace std;

void binary_insertion(vector<Player> &vet, Player player, int left, int right);

int main(){
    vector<Player> vet;

    Player p1 ("1", "Messi", "Lionel Messi", "RW", "Argentina", "FC Barcelona", "Spain Primera Division");
    Player p2 ("2", "Cristiano Ronaldo", "Cristiano Ronaldo", "ST", "Portugal", "Juventus", "Italian Serie A");
    Player p3 ("3", "Neymar Jr", "Neymar da Silva Santos Jr", "LW", "Brazil", "Paris Saint-Germain", "French Ligue 1");
    Player p4 ("4", "De Bruyne", "Kevin De Bruyne", "CAM", "Belgium", "Manchester City", "English Premier League");

    vet.push_back(p1);
    vet.push_back(p2);
    vet.push_back(p3);
    vet.push_back(p4);

    p1.update_rating(94);
    p2.update_rating(93);
    p3.update_rating(92);

    binary_insertion(vet, p1, 0, vet.size());
    binary_insertion(vet, p2, 0, vet.size());
    binary_insertion(vet, p3, 0, vet.size());
    binary_insertion(vet, p4, 0, vet.size());

    for(int i = 0; i < vet.size(); i++){
        cout << vet[i].short_name << " " << vet[i].rate << endl;
    }

    return 0;
}

//reordenar vetor com 

void binary_update(vector<Player> &vet, Player player, int left, int right){
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
}*/

