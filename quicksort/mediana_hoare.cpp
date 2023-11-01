#include <bits/stdc++.h>

using namespace std;

int partition_hoare(vector <int> C, int left, int right);
void quicksort(vector <int> c, int i, int f);

int main(){
    
    return 0;
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

void quicksort(vector <int> c, int i, int f){
    int p;

    if(f > i){
        p = partition_hoare(c, i, f);
        quicksort(c, i, p-1);
        quicksort(c, p+1, f);
    }
}