#include <bits/stdc++.h>  
#include "hashtable.h" 

using namespace std;

int main(int argc, char *argv[]){
    Hashtable hashtable(50, 1);
    string line;

    getline(cin, line);
    while(getline(cin, line)){
        // exemplo de linha com dados do jogador a serem pegos
        // 200389,J. Oblak,Jan Oblak,GK,Slovenia,Atlético Madrid,Spain Primera Division

        int token = line.find_first_of(',');
        int id = stoi(line.substr(0, token));

        int token2 = line.find_first_of(',', token+1);
        string short_name = line.substr(token+1, token2 - token-1);

        int token3 = line.find_first_of(',', token2+1);
        string long_name = line.substr(token2+1, token3 - token2-1);

        int token4 = line.find_first_of(',', token3+1);
        string position = line.substr(token3+1, token4 - token3-1);

        int token5 = line.find_first_of(',', token4+1);
        string nacionality = line.substr(token4+1, token5 - token4-1);

        int token6 = line.find_first_of(',', token5+1);
        string club = line.substr(token5+1, token6 - token5-1);

        int token7 = line.find_first_of(',', token6+1);
        string league = line.substr(token6+1, token7 - token6-1);

        Players player(id, short_name, long_name, position, nacionality, club, league);
        hashtable.insereJogador(player);
    }

    hashtable.printa_hashtable();

    return 0;
}
