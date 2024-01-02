#include <bits/stdc++.h>
using namespace std;

class Players{
    public:
        int id;
        string short_name;
        string long_name;
        string position;
        string nacionality;
        string club;
        string league;

        Players(int id, string short_name, string long_name, string position, string nacionality, string club, string league){
            this->id = id;
            this->short_name = short_name;
            this->long_name = long_name;
            this->position = position;
            this->nacionality = nacionality;
            this->club = club;
            this->league = league;
        }
};

