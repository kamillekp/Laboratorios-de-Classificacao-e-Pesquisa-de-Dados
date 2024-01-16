#include <bits/stdc++.h>  
#include "hashtable_Player.hpp" 
#include "hashtable_User.hpp" 
#include "Trie.hpp"
#include "Trie_user.hpp"

using namespace std;

#define HASH_PLAYER 30
#define HASH_USER 200
#define PLAYERS_FILE "playerscopy.csv"
#define RATING_FILE "consultas.csv"
#define TAG_FILE "tags.csv"

void menu(int *op);

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
    vector<string> tags_entrada;
    int num_linhas = tags_entrada.size();
    vector<vector<int>> ids_tags(num_linhas);
    vector<int> aux;
    stringstream ss; // Add this line

    menu(&op);

    string id_string;

    switch (op){
        case 1:
            cout << "Digite o prefixo: ";
            cin >> prefix;
            
            ids = trie_players.get_ids(trie_players.catch_prefix(trie_players.get_root(), prefix));

            for(int i = 0; i < ids.size(); i++){
                id_string= to_string(ids[i]);
                hashtable_player.binary_insertion(printa, hashtable_player.find_player(id_string), 0, printa.size());
            }
       
            for(int i = 0; i < printa.size(); i++){
                hashtable_player.print_player1(stoi(printa[i].id));
            }

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:{
            string tag_name;
            vector<string> tags_entrada;
            vector<vector<int>> ids_tags;
            vector<int> aux;

            cout << "Digite a tag (exemplo: 'Brazil' 'Primera Division'): ";
            cin.ignore();
            getline(cin, tag_name);

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

void menu(int *op){
    cout << "-----------------------------------\tMENU\t-----------------------------------" << endl;
    cout << "1 - Pesquisar por prefixo." << endl;
    cout << "2 - Pesquisar avaliacoes do usuario." << endl;
    cout << "3 - Pesquisar melhores jogadores de uma posicao." << endl;
    cout << "4 - Pesquisar por tags." << endl;

    cout << "Digite a opcao desejada: ";
    cin >> *op;
}


