#include <bits/stdc++.h>  
#include "hashtable.h" 

using namespace std;

int main(){
    Hashtable hashtable(7);
    string line;

    getline(cin, line);
    while(getline(cin, line)){
        int token = line.find_first_of(',');
        int id = stoi(line.substr(0, token));

        int token2 = line.find_first_of(',', token+1);
        string name = line.substr(token+1, token2 - token-1);
        
        string position = line.substr(token2+1, line.size() - token2-1);

        Players player(id, name, position);
    
        hashtable.insereJogador(player);
    }

    hashtable.printa_hashtable();

    return 0;
}
