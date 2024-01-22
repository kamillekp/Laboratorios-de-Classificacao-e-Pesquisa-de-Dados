#include <bits/stdc++.h>

using namespace std;

typedef struct node_{
    char data;
    vector<struct node_*> children;
    bool is_end;
    vector<int> ids;
}NODE_;

class Trie_User{
private:
    NODE_* root;
    int size;
public:
    Trie_User();
    void insert (string word, int id_player);
    void print(NODE_* root);        // APAGAR DEPOIS
    NODE_* get_root(){return root;}
    NODE_* catch_tag(NODE_* root, string tag);
    vector<int> get_ids(NODE_* root);
};

Trie_User::Trie_User(){
    root = new NODE_;
    root->data = ' ';
    root->is_end = false;
    size = 0;
}

void Trie_User::insert(string word, int id_player){
    NODE_* current = root;

    if (current == NULL)
        return;

    for (int i = 0; i < word.length(); i++){
        NODE_* child = NULL;
        for (int j = 0; j < current->children.size(); j++){
            if (current->children[j]->data == word[i]){
                child = current->children[j];
                break;
            }
        }

        if (child == NULL){
            child = new NODE_;
            child->data = word[i];
            child->is_end = false;
            current->children.push_back(child);
        }

        current = child;
    }

    current->is_end = true;

    for(int i = 0; i < current->ids.size(); i++){
        if(current->ids[i] == id_player){
            return;
        }
    }

    current->ids.push_back(id_player);
}

void Trie_User::print(NODE_* root){
    if (root == NULL)
        return;

    for (int i = 0; i < root->children.size(); i++){
        cout << root->children[i]->data << " ";
        print(root->children[i]);
    }
}

NODE_* Trie_User::catch_tag(NODE_* root, string tag){
    NODE_* current = root;

    if (current == NULL)
        return NULL;

    for (int i = 0; i < tag.length(); i++){
        NODE_* child = NULL;

        for (int j = 0; j < current->children.size(); j++){
            if (current->children[j]->data == tag[i]){
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

vector<int> Trie_User::get_ids(NODE_* root){
    return root->ids;
}