#include<iostream>
#include<string>
#include<vector>

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
    void remove(string word, int id_player);
    TRIE_NODE* get_root(){return root;}
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
    for (int i = 0; i < word.length(); i++)
    {
        TRIE_NODE* child = NULL;
        int j;
        for (j = 0; j < current->children.size(); j++)
        {
            if (current->children[j]->data == word[i])
            {
                child = current->children[j];
                break;
            }
        }
        if (child == NULL)
        {
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

void Trie::remove(string word, int id_player){
    TRIE_NODE* current = root;
    if (current == NULL)
        return;
    for (int i = 0; i < word.length(); i++)
    {
        TRIE_NODE* child = NULL;
        int j;
        for (j = 0; j < current->children.size(); j++)
        {
            if (current->children[j]->data == word[i])
            {
                child = current->children[j];
                break;
            }
        }
        if (child == NULL)
        {
            return;
        }
        current = child;
    }
    current->is_end = id_player;
    size--;
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
