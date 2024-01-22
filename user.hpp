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