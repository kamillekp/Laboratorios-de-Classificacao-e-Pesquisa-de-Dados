#include <bits/stdc++.h>  
#include "hashtable_Player.hpp" 
#include "hashtable_User.hpp" 
#include "Trie_user.hpp"
#include "Trie.hpp"
#include "parsing.hpp"

using namespace std;
using namespace aria::csv;

// VARIÁVEIS GLOBAIS
#define HASH_PLAYER 9473
#define HASH_USER 9997000
#define PLAYERS_FILE ".\\arquivos-parte1\\players.csv"
#define RATING_FILE ".\\rating.csv"
#define TAG_FILE ".\\arquivos-parte1\\tags.csv"


//-------------------------------------------------------------------------------------------------------------------------------------------
// INICIALIZANDO AS HASHTABLES
Hashtable_Player hashtable_player(HASH_PLAYER);
Hashtable_User hashtable_user(HASH_USER);


//-------------------------------------------------------------------------------------------------------------------------------------------
// STRUCT AUXILIAR E FUNÇÕES AUXILIARES PARA A PESQUISA 2
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


//-------------------------------------------------------------------------------------------------------------------------------------------
// FUNÇÃO AUXILIAR PARA A PESQUISA 4
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


//-------------------------------------------------------------------------------------------------------------------------------------------
int main(){
    clock_t start, end;
    string line;
    ifstream file;
    Trie trie_players;
    Trie_User trie_tags;


//-------------------------------------------------------------------------------------------------------------------------------------------
    // ENTRADA PADRÃO DO ARQUIVO PRINCIPAL COM OS DADOS DOS JOGADORES
    string id, id_user, short_name, long_name, position, nacionality, club, league;
    int indice = 0;

    ifstream file_players(PLAYERS_FILE);
    

    if(!file_players.is_open()){
        cout << "Arquivo players nao encontrado." << endl;
        return 0;
    }

    CsvParser parser_players(file_players);

    for (auto row:parser_players){   
        if(indice == 0){
            indice++;
            continue;
        }

        id = row[0];
        short_name = row[1];
        long_name = row[2];
        position = row[3];
        nacionality = row[4];
        club = row[5];
        league = row[6];

        // INSERE NA HASH OS DADOS DO PLAYER
        hashtable_player.insert_player(Player (id, short_name, long_name, position, nacionality, club, league));

        // INSERE NA TRIE OS DADOS DO PLAYER
        trie_players.insert(long_name, stoi(id));
    }

    indice = 0;
    file_players.close();


//-------------------------------------------------------------------------------------------------------------------------------------------
    //  ENTRADA DO ARQUIVO COM AVALIAÇÕES DOS USUÁRIOS
    string rating;

    ifstream file_ratings(RATING_FILE);
    

    if(!file_ratings.is_open()){
        cout << "Arquivo ratings nao encontrado." << endl;
        return 0;
    }

    CsvParser parser_ratings(file_ratings);

    for (auto row:parser_ratings){   
        if(indice == 0){
            indice++;
            continue;
        }

        id_user = row[0];
        id = row[1];
        rating = row[2];

        // ATUALIZA A AVALIAÇÃO DO PLAYER
        hashtable_player.update_rating(id, stof(rating));

        // INSERE NA HASH OS DADOS DO USER
        hashtable_user.insert_user(User(id_user, id, rating));
    }

    indice = 0;
    file_players.close();


//-------------------------------------------------------------------------------------------------------------------------------------------
    //  ENTRADA DO ARQUIVO COM AS CONSULTAS USANDO TAGS
    string tag;

    ifstream file_tags(TAG_FILE);

    if(!file_tags.is_open()){
        cout << "Arquivo tags nao encontrado." << endl;
        return 0;
    }

    CsvParser parser_tags(file_tags);

    for (auto row:parser_tags){   
        if(indice == 0){
            indice++;
            continue;
        }

        id_user = row[0];
        id = row[1];
        tag = row[2];

        // INSERE NA TRIE OS DADOS DA TAG
        trie_tags.insert(tag, stoi(id));
    }

    indice = 0;
    file_tags.close();

    end = clock();
    cout << "Tempo de insercao: " << (double)(end - start) / CLOCKS_PER_SEC << " S" << endl;


//-------------------------------------------------------------------------------------------------------------------------------------------
    // MENU DE OPÇÕES
    vector<Player> printa, players_vet, printa_players;
    vector<Player_User> printa2, aux_pu, principal;

    vector<User> user_ratings;
    vector<string> tags_entrada;
    vector<int> aux, ids;

    int num_linhas = tags_entrada.size();
    vector<vector<int>> ids_tags(num_linhas);

    string entrada, top_num, top_pos, e1;
    string prefix, tag_name, id_string;
    int j = 0, k = 0, op;


//-------------------------------------------------------------------------------------------------------------------------------------------
    // VERIFICA QUAL SINTAXE O USUÁRIO USOU
    cout << "Digite a opcao desejada: " << endl;
    getline(cin, entrada);

    stringstream ss2(entrada);
    getline(ss2, e1, ' ');


//-------------------------------------------------------------------------------------------------------------------------------------------
    // DETERMINA OP
    if(e1 == "player"){
        getline(ss2, prefix, ' ');
        op = 1;
    }
    else if(e1 == "user"){
        getline(ss2, id_user, ' ');
        op = 2;
    }
    else if(e1 == "top"){
        getline(ss2, top_num, ' ');
        getline(ss2, top_pos, ' ');
        op = 3;
    }
    else if(e1 == "tags"){
        getline(ss2, tag_name, '\0');
        op = 4;
    }   
    

//-------------------------------------------------------------------------------------------------------------------------------------------
    // EXECUTA A OPÇÃO ESCOLHIDA
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

            // insere na print2
            for(int i = 0; i < printa.size(); i++){
                printa2.push_back(Player_User{printa[i], stof(user_ratings[i].rate)});
            }

            // ordena printa2 por rate_user
            do{
                while(printa2[j].rate_user == printa2[k].rate_user){
                    binary_insertion(aux_pu, printa2[k], 0, aux_pu.size());
                    k++;
                }

                principal.insert(principal.end(), aux_pu.begin(), aux_pu.end());

                aux_pu.clear();
                j = k;

            }while((printa2.size() - k) > 0);

            pesquisa2(principal);

            break;


//-------------------------------------------------------------------------------------------------------------------------------------------
        case 3:
            players_vet = hashtable_player.find_players_by_position(top_pos);

            for(int i = 0; i < players_vet.size(); i++){
                hashtable_player.binary_insertion(printa_players, players_vet[i], 0, printa_players.size());
            }

            for(int i = 0; i < stoi(top_num); i++){
                cout << printa_players[i].short_name << " " << printa_players[i].position << " " << printa_players[i].rate << endl;
            }

            break;


//-------------------------------------------------------------------------------------------------------------------------------------------
        case 4:{
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


//-------------------------------------------------------------------------------------------------------------------------------------------
        default:
            cout << "Opcao invalida." << endl;
            break;
    }

    return 0;
}