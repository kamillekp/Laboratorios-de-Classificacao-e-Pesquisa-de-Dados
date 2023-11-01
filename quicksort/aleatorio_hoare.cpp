#include <bits/stdc++.h>

using namespace std;

int random(int i, int f);   
int partition_hoare(vector <int> C, int left, int right);
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

int partition_hoare(vector <int> C, int left, int right) {
    int chave, i, j;
    chave = C[left]; i = left; j = right+1;

    while (1) {
        while (C[++i] <= chave) if (i == right) break;
            while (chave < C[--j]) if (j == left) break;
                if (i >=j) break;
                    swap(C[i],C[j]);
    }

    swap(C[left], C[j]);
    return j;
}

void quicksort_randomizado(vector <int> c, int i, int f){
    int p, r;

    if(f > i) {
        r = random(i,f);

        swap(c[i], c[r]);
        p = partition_hoare(c,i,f);
        quicksort_randomizado(c, i, p-1);
        quicksort_randomizado(c, p+1, f);
    }
}