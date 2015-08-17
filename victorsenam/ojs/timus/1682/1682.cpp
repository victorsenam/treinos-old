#include <bits/stdc++.h>

using namespace std;

const int K = 100007;

vector<int> v[K][2];
int uf[2*K];
int we[2*K];
int k;

int join(int a, int b) {
    
}

int find (int a) {
    if (uf[uf[a]] != uf[a])
        uf[a] = find(uf[a]);
    return uf[a];
}

int main () {
    scanf("%d", &k);

    for (int i = 0; i <= 2*k; i++)
        uf[i] = i;
}
