#include <bits/stdc++.h>  
#include "hashtable_Player.hpp" 
#include "hashtable_User.hpp" 
#include "Trie.hpp"

using namespace std;

#define HASH_PLAYER 30
#define HASH_USER 200
#define PLAYERS_FILE "playerscopy.csv"
#define RATING_FILE "consultas.csv"
#define TAG_FILE "tags.csv"

void menu(int *op);

int main(){
    string id, id_user, short_name, long_name, position, nacionality, club, league, rating, tag;
    string line;
    ifstream file;
    Trie trie_players, trie_tags;

    string prefix, user_ID, tag_name, pos;
    vector<int> ids;            
    int top, op;        


//-------------------------------------------------------------------------------------------------------------------------------------------
//  ENTRADA PADRÃO DO ARQUIVO PRINCIPAL COM OS DADOS DOS JOGADORES
    Hashtable_Player hashtable_player(HASH_PLAYER);

    file.open(PLAYERS_FILE);

    if(!file.is_open()){
        cout << "Arquivo nao encontrado." << endl;
        return 0;
    }

    //SEPARANDO DADOS DE CADA JOGADOR
    getline(file, line);
    while(getline(file, line)){
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

    file.close();

    //trie_players.print(trie_players.get_root());
    //hashtable_player.print_hashtable();
    //hashtable_player.print_player1(214977);


//-------------------------------------------------------------------------------------------------------------------------------------------
//  ENTRADA DO ARQUIVO COM AVALIAÇÕES DOS USUÁRIOS
    Hashtable_User hashtable_user(HASH_USER);

    file.open(RATING_FILE);

    if(!file.is_open()){
        cout << "Arquivo nao encontrado." << endl;
        return 0;
    }

    // SEPARANDO DADOS DE CADA AVALIAÇÃO
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);

        getline(ss, id_user, ',');
        getline(ss, id, ',');
        getline(ss, rating, ',');

        hashtable_player.update_rating(id, stof(rating));
        hashtable_user.insert_user(User(id_user, id, rating));
    }

    file.close();

    //hashtable_user.print_hashtable();
    //hashtable_player.print_player1(214977);


//-------------------------------------------------------------------------------------------------------------------------------------------
//  ENTRADA DO ARQUIVO COM AS CONSULTAS USANDO TAGS
    file.open(TAG_FILE);

    if(!file.is_open()){
        cout << "Arquivo nao encontrado." << endl;
        return 0;
    }

    // SEPARANDO DADOS DE CADA TAG
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


//-------------------------------------------------------------------------------------------------------------------------------------------
// MENU DE OPÇÕES
    menu(&op);

    switch (op){
        case 1:
            cout << "Digite o prefixo: ";
            cin >> prefix;

            ids = trie_players.get_ids(trie_players.catch_prefix(trie_players.get_root(), prefix));

            cout << "\n1) sofifa_id, " << "2) short_name, " << "3) long_name, " << "4) player_positions, " << "5) rating, " << "6) count" <<  endl;
            if(ids.size() == 0){
                cout << "Nenhum jogador encontrado." << endl;
                break;
            }

            for(int i = 0; i < ids.size(); i++){
                hashtable_player.print_player1(ids[i]);
            }

            break;
        case 2:
            break;
        case 3:
            break;
        case 4: 
            break;
        default:
            break;
    }

    return 0;
}

void menu(int *op){
    cout << "-----------------------------------\tMENU\t-----------------------------------" << endl;
    cout << "1 - Pesquisar por prefixo." << endl;
    cout << "2 - Pesquisar avaliacoes do usuario." << endl;
    cout << "3 - Pesquisar melhores jogadores de uma posicao." << endl;
    cout << "4 - Pesquisar por tags." << endl;

    cout << "Digite a opcao desejada: ";
    cin >> *op;
}