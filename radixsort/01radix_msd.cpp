#include <bits/stdc++.h>

using namespace std;

void msd_sort(vector<int>& arr, int exp, vector<int>& sorted_arr);
int get_max_exp(vector<int>& arr);
void print(vector<int>& arr);

int main() {
    string texto, palavras[10];
    int i = 0;

    fstream arquivo("texto.txt");
    getline(arquivo, texto);

    for (char c : texto) {
    if (c == ' ') {
        palavras[i++] = "";
    } else {
        palavras[i] += c;
    }
    }

    if (!palavras[i].empty()) i++;

    for (int j = 0; j < i; j++) cout << palavras[j] << " ";
    cout << endl;

    return 0;
}


// Function to sort the given array using MSD Radix Sort recursively
void msd_sort(vector<int>& arr, int exp, vector<int>& sorted_arr) {
    if (exp <= 0) {
        return;
    }

    int n = arr.size();
    vector<int> output(n, 0);
    vector<int> count(10, 0);

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // Recursive sorting for each bucket
    for (int i = 0; i < 10; i++) {
        if (count[i] > 1) {
            msd_sort(arr, exp / 10, sorted_arr);
        } else if (count[i] == 1) {
            sorted_arr.push_back(output[i]);
        }
    }
}

// Function to calculate the MSD of the maximum value in the array
int get_max_exp(vector<int>& arr) {
    int mx = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }

    int exp = 1;

    while (mx > 10) {
        mx /= 10;
        exp *= 10;
    }

    return exp;
}

// Function to print an array
void print(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}