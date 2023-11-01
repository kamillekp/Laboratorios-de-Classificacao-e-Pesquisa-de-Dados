#include <bits/stdc++.h>

using namespace std;

int random(int i, int f);
int partition_lomuto(vector <int> C, int left, int right);
void quicksort_randomizado(vector <int> c, int i, int f);

int main(){

    return 0;
}

int random(int i, int f){
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(i, f); 

    return dist(gen);   
}

int partition_lomuto(vector <int> C, int left, int right){
    int chave = C[left];
    int storeindex = left + 1; 

    for (int i = left+1; i <= right; i++) {
        if (C[i] < chave){
            swap(C[i], C[storeindex]);
            storeindex++; 
        }
    }

    swap(C[left], C[storeindex-1]);

    return (storeindex-1);
}

void quicksort_randomizado(vector <int> c, int i, int f){
    int p, r;

    if(f > i) {
        r = random(i,f);

        swap(c[i], c[r]);
        p = partition_lomuto(c,i,f);
        quicksort_randomizado(c, i, p-1);
        quicksort_randomizado(c, p+1, f);
    }
}