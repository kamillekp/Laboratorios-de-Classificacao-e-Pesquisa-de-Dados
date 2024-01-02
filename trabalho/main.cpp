#include <bits/stdc++.h>  
#include "hashtable_Player.h" 
#include "hashtable_User.h" 

using namespace std;

int main(int argc, char *argv[]){
    string id, id_user, short_name, long_name, position, nacionality, club, league, rating;
    string line;

    //---------------------------------------------------------------------------------------------------------
    // ENTRADA PADRÃO DO ARQUIVO PRINCIPAL COM OS DADOS DOS JOGADORES
    Hashtable_Player hashtable_player(30);
    getline(cin, line);
    while(getline(cin, line)){
        stringstream ss(line);

        getline(ss, id, ',');
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

        hashtable_player.insert_player(Player (id, short_name, long_name, position, nacionality, club, league));
    }

    //hashtable_player.print_hashtable();

    //---------------------------------------------------------------------------------------------------------
    //ENTRADA DO ARQUIVO COM AVAALIAÇÕES DOS USUÁRIOS
    Hashtable_User hashtable_user(200);

    ifstream file;
    file.open(argv[1]);

    if(!file.is_open()){
        cout << "Arquivo nao encontrado." << endl;
        return 0;
    }

    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);

        getline(ss, id_user, ',');
        getline(ss, id, ',');
        getline(ss, rating, ',');

        hashtable_user.insert_user(User(id_user, id, rating));
    }

    //hashtable_user.print_hashtable();

    return 0;
}
