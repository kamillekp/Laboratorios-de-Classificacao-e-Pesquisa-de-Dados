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
        float rating;
        int counts;

        Player(string id, string short_name, string long_name, string position, string nacionality, string club, string league){
            this->id = id;
            this->short_name = short_name;
            this->long_name = long_name;
            this->position = position;
            this->nacionality = nacionality;
            this->club = club;
            this->league = league;
            this->rating = 0;
            this->counts = 0;
        }

        void update_rating(float rating){
            this->rating += rating;
            this->counts++;
        }
};

