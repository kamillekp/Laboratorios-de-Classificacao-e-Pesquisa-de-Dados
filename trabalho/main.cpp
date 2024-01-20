#include <bits/stdc++.h>  
#include "hashtable_Player.hpp" 
#include "hashtable_User.hpp" 
#include "Trie.hpp"
#include "Trie_user.hpp"

using namespace std;

#define HASH_PLAYER 30
#define HASH_USER 200
#define PLAYERS_FILE ".\\arquivos-parte1\\players.csv"
#define RATING_FILE ".\\arquivos-parte1\\minirating.csv"
#define TAG_FILE ".\\arquivos-parte1\\tags.csv"

typedef struct Player_User{
    Player player;
    float rate_user;
}player_user;

void pesquisa2(vector<Player_User> &vet){
    for(int i = 0; i < vet.size(); i++){
        cout << "1) " << vet[i].player.id << ", 2) " << vet[i].player.short_name << ", 3) " << vet[i].player.long_name << ", 4) " << vet[i].player.rate << ", 5) " << vet[i].player.counts << ", 6) " << vet[i].rate_user << endl;
    }
}
void binary_insertion(vector<Player_User> &vet, Player_User user, int left, int right){
    if(vet.size() == 0){
        vet.push_back(user);
        return;
    }

    int mid = (left + right) / 2;

    if(left == right){
        vet.insert(vet.begin() + mid, user);
        return;
    }

    if(user.player.rate < vet[mid].player.rate)
        binary_insertion(vet, user, mid+1, right);
    else
        binary_insertion(vet, user, left, mid);
}
vector<string> tokenize(const string& input, const string& delimiters) {
    vector<string> tokens;
    stringstream ss(input);
    string token;

    while (getline(ss, token)) {
        size_t pos = 0;
        while ((pos = token.find_first_of(delimiters)) != string::npos) {
            if (pos > 0) {
                tokens.push_back(token.substr(0, pos));
            }
            token.erase(0, pos + 1);
        }
        if (!token.empty() && token != "" && token != "\n" && token != "") {
            tokens.push_back(token);
        }
    }

    return tokens;
}
vector<string> splitString(const string& input, char delimiter) {
    vector<string> result;
    string token;
    
    for (char ch : input) {
        if (ch == delimiter) {
            if (!token.empty()) {
                result.push_back(token);
            }
            token.clear();
        } else {
            token += ch;
        }
    }
    
    if (!token.empty()) {
        result.push_back(token);
    }
    
    return result;
}

int main(){
    string id, id_user, short_name, long_name, position, nacionality, club, league, rating, tag;
    string line;
    ifstream file;
    Trie trie_players;
    Trie_User trie_tags;

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
    //ordenar os players aqui
    vector<Player> printa;
    vector<Player_User> printa2;
    vector<Player_User> aux_pu;
    vector<Player_User> principal;
    vector<User> user_ratings;
    vector<string> tags_entrada;
    int num_linhas = tags_entrada.size();
    vector<vector<int>> ids_tags(num_linhas);
    vector<int> aux;
    stringstream ss;
    int j = 0;
    int k = 0;
    string entrada;
    string e1;

    // MENU DE OPÇÕES
    cout << "Digite a opcao desejada: " << endl;
    getline(cin, entrada);

    stringstream ss2(entrada);
    getline(ss2, e1, ' ');

    if(e1 == "player"){
        getline(ss2, prefix, ' ');
        op = 1;
    }
    else if(e1 == "user"){
        getline(ss2, id_user, ' ');
        op = 2;
    }
    else if(e1 == "top"){

        op = 3;
    }
    else if(e1 == "tags"){
        getline(ss2, tag_name, '\0');
        op = 4;
    }   
    
    string id_string;

    switch (op){
        case 1:
            ids = trie_players.get_ids(trie_players.catch_prefix(trie_players.get_root(), prefix));

            for(int i = 0; i < ids.size(); i++){
                id_string= to_string(ids[i]);
                hashtable_player.binary_insertion(printa, hashtable_player.find_player(id_string), 0, printa.size());
            }
       
            for(int i = 0; i < printa.size(); i++){
                hashtable_player.print_player1(stoi(printa[i].id));
            }

            printa.clear();

            break;


    //-------------------------------------------------------------------------------------------------------------------------------------------
        case 2:
            // insere em user_ratings ordenando pelo rate
            user_ratings = hashtable_user.find_user_ratings(id_user);

            // pega players com os ids de user_ratings
            for(int i = 0; i < user_ratings.size(); i++){
                printa.push_back(hashtable_player.find_player(user_ratings[i].id_player));
            }

            // inserir na print2
            for(int i = 0; i < printa.size(); i++){
                printa2.push_back(Player_User{printa[i], stof(user_ratings[i].rate)});
            }

            //iniciaWhile:
            do{
                while(printa2[j].rate_user == printa2[k].rate_user){
                    binary_insertion(aux_pu, printa2[k], 0, aux_pu.size());
                    k++;
                }

                principal.insert(principal.end(), aux_pu.begin(), aux_pu.end());

                aux_pu.clear();
                j = k;
            }while((printa2.size() - k) > 0);
            //if((printa2.size() - k) > 0)
                //goto iniciaWhile;

            pesquisa2(principal);

            break;


    //-------------------------------------------------------------------------------------------------------------------------------------------
        case 3:
            break;

            
    //-------------------------------------------------------------------------------------------------------------------------------------------
        case 4:{
            vector<string> tags_entrada;
            vector<vector<int>> ids_tags;
            vector<int> aux;

            // separa tags
            tags_entrada = splitString(tag_name, '\'');
            
            //excluindo espaços em branco da tags_entrada
            for(int i = 0; i < tags_entrada.size(); i++){
                if(tags_entrada[i] == " "){
                    tags_entrada.erase(tags_entrada.begin() + i);
                }
            }

            // achar ids das tags
            for(int i = 0; i < tags_entrada.size(); i++){
                ids = trie_tags.get_ids(trie_tags.catch_tag(trie_tags.get_root(), tags_entrada[i]));
                ids_tags.push_back(ids);
            }
        
            // achar interseccao entre as linhas da matriz
            aux = ids_tags[0];
            for(int i = 1; i < ids_tags.size(); i++){
                for(int j = 0; j < aux.size(); j++){
                    for(int k = 0; k < ids_tags[i].size(); k++){
                        if(aux[j] == ids_tags[i][k]){
                            break;
                        }
                        else if(k == ids_tags[i].size() - 1){
                            aux.erase(aux.begin() + j);
                            j--;
                        }
                    }
                }
            }

            // ordenar os ids
            for(int i = 0; i < aux.size(); i++){
                id_string= to_string(aux[i]);
                hashtable_player.binary_insertion(printa, hashtable_player.find_player(id_string), 0, printa.size());
            }

            // printar os ids
            for(int i = 0; i < printa.size(); i++){
                hashtable_player.print_player4(stoi(printa[i].id));
            }

            break;}
        default:
            break;
    }

    return 0;
}


