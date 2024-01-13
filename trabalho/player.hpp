#include <bits/stdc++.h>
using namespace std;

class Player{
    public:
        string id;
        string short_name;
        string long_name;
        string position;
        string nacionality;
        string club;
        string league;

        Player(string id, string short_name, string long_name, string position, string nacionality, string club, string league){
            this->id = id;
            this->short_name = short_name;
            this->long_name = long_name;
            this->position = position;
            this->nacionality = nacionality;
            this->club = club;
            this->league = league;
        }
};

