#include <bits/stdc++.h>

using namespace std;

typedef struct TrieNode{
    char data;
    vector<struct TrieNode*> children;
    int is_end;
}TRIE_NODE;

class Trie{
private:
    TRIE_NODE* root;
    int size;
public:
    Trie();
    ~Trie();
    void insert (string word, int id_player);
    void print(TRIE_NODE* root);
    TRIE_NODE* get_root(){return root;}
    TRIE_NODE* catch_prefix(TRIE_NODE* root, string prefix);
    vector<int> get_ids(TRIE_NODE* root);
};

Trie::Trie(){
    root = new TRIE_NODE;
    root->data = ' ';
    root->is_end = 0;
    size = 0;
}

Trie::~Trie(){
    delete root;
}

void Trie::insert(string word, int id_player){
    TRIE_NODE* current = root;
    if (current == NULL)
        return;

    for (int i = 0; i < word.length(); i++){
        TRIE_NODE* child = NULL;

        for (int j = 0; j < current->children.size(); j++){
            if (current->children[j]->data == word[i]){
                child = current->children[j];
                break;
            }
        }

        if (child == NULL){
            child = new TRIE_NODE;
            child->data = word[i];
            child->is_end = 0;
            current->children.push_back(child);
        }

        current = child;
    }

    current->is_end = id_player;
    size++;
}

void Trie::print(TRIE_NODE* root){
    if(root == NULL)
        return;
    else{
        cout << root->is_end << " ";
    }

    for(int i = 0; i < root->children.size(); i++){
        print(root->children[i]);
    }
}

TRIE_NODE* Trie::catch_prefix(TRIE_NODE* root, string prefix){ //retorna o no a partir de um prefixo
    TRIE_NODE* current = root;

    if (current == NULL)
        return NULL;

    for (int i = 0; i < prefix.length(); i++){
        TRIE_NODE* child = NULL;

        for (int j = 0; j < current->children.size(); j++){
            if (current->children[j]->data == prefix[i]){
                child = current->children[j];
                break;
            }
        }
        
        if (child == NULL)
            return NULL;

        current = child;
    }

    return current;
}

vector<int> Trie::get_ids(TRIE_NODE* root){//retorna os ids a partir de um no
    vector<int> ids;

    if(root == NULL)
        return ids;
    else{
        if(root->is_end != 0)
            ids.push_back(root->is_end);
    }

    for(int i = 0; i < root->children.size(); i++){
        vector<int> aux = get_ids(root->children[i]);
        ids.insert(ids.end(), aux.begin(), aux.end());
    }

    return ids;
}

