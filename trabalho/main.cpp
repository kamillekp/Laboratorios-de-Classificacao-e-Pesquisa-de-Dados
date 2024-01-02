#include <bits/stdc++.h>  
#include "hashtable_Player.h" 
#include "hashtable_User.h" 

using namespace std;

int main(int argc, char *argv[]){
    Hashtable_Player hashtable(50);
    string line;


    // ENTRADA PADRÃO DO ARQUIVO PRINCIPAL COM OS DADOS DOS JOGADORES
    //20801,Cristiano Ronaldo,Cristiano Ronaldo dos Santos Aveiro,"ST, LW",Portugal,Juventus,Italian Serie A

    getline(cin, line);
    while(getline(cin, line)){
        stringstream ss(line);
        string idS, short_name, long_name, position, nacionality, club, league;

        getline(ss, idS, ',');
        getline(ss, short_name, ',');
        getline(ss, long_name, ',');

        if(line.find("\"") != string::npos){
            getline(ss, position, '\"');
            getline(ss, position, '\"');
            getline(ss, nacionality, ',');
        }
        else
            getline(ss, position, ',');

        getline(ss, nacionality, ',');
        getline(ss, club, ',');
        getline(ss, league, ',');

        int id = stoi(idS);

        Player player(id, short_name, long_name, position, nacionality, club, league);
        hashtable.insert_player(player);
    }

    hashtable.print_hashtable();

    //---------------------------------------------------------------------------------------------------------
    //ENTRADA DO ARQUIVO COM AVAALIAÇÕES DOS USUÁRIOS
    // Hashtable_User hashtable_user(50);

    // ifstream file(argv[1]);
    // while(getline(file, line)){
    //     //exemplo de linha para leitura
        
    // }

    return 0;
}
