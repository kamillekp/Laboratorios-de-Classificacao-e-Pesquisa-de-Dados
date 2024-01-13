#include <bits/stdc++.h>  
#include "hashtable_Player.hpp" 
#include "hashtable_User.hpp" 
#include "Trie.hpp"

#define HASH_PLAYER 30
#define HASH_USER 200
#define RATING_FILE "consultas.csv"
#define TAG_FILE "tags.csv"

using namespace std;

int main(){
    string id, id_user, short_name, long_name, position, nacionality, club, league, rating, tag;
    string line;
    ifstream file;
    Trie trie_players;
    Trie trie_tags;

    //---------------------------------------------------------------------------------------------------------
    // ENTRADA PADRÃO DO ARQUIVO PRINCIPAL COM OS DADOS DOS JOGADORES
    Hashtable_Player hashtable_player(HASH_PLAYER);
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

        // INSERE NA HASH OS DADOS DO PLAYER
        hashtable_player.insert_player(Player (id, short_name, long_name, position, nacionality, club, league));

        // INSERE NA TRIE OS DADOS DO PLAYER
        trie_players.insert(long_name, stoi(id));
    }


    //trie_players.print(trie.get_root());
    //hashtable_player.print_hashtable();


    //---------------------------------------------------------------------------------------------------------
    //ENTRADA DO ARQUIVO COM AVALIAÇÕES DOS USUÁRIOS
    Hashtable_User hashtable_user(HASH_USER);

    file.open(RATING_FILE);

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

    file.close();

    //hashtable_user.print_hashtable();


    //---------------------------------------------------------------------------------------------------------
    // ENTRADA DO ARQUIVO COM AS CONSULTAS USANDO TAGS
    file.open(TAG_FILE);

    if(!file.is_open()){
        cout << "Arquivo nao encontrado." << endl;
        return 0;
    }

    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);

        getline(ss, id_user, ',');
        getline(ss, id, ',');
        getline(ss, tag, ',');

        trie_tags.insert(tag, stoi(id));
    }

    file.close();

    //trie_tags.print(trie_tags.get_root());

    op = menu();

    switch (op){
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }
    return 0;
}
