#include <bits/stdc++.h>
#include "tag.h"

using namespace std;

class Hashtable_Tag {
    private:
        vector<vector<Tag>> hashtable;
        int ocupadas;
        int consultas;
        int MAX;
        
    public:
        Hashtable_Tag(int MAX){
            this->MAX = MAX;
            this->ocupadas = 0;
            this->consultas = 0;
            this->hashtable.resize(MAX);
        }

        void insert_tag (Tag tag){
            int ind = stoi(tag.id) % MAX;

            if(hashtable[ind].size() == 0){
                ocupadas++;
            }

            hashtable[ind].push_back(tag);
        }

        Tag find_tag (string id){
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
                    cout << "[" << hashtable[i][j].id << ":" << hashtable[i][j].id_player << ":" << hashtable[i][j].tag << "] -> ";
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