#include <bits/stdc++.h>

using namespace std;

const int K = 100007;

vector<int> v[2][K];
int uf[3*K];
int we[3*K];
int k, a[2];

int find (int a) {
    if (uf[uf[a]] != uf[a])
        uf[a] = find(uf[a]);
    return uf[a];
}

int join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) 
        return a;
    if (we[a] > we[b])
        swap(a, b);
    uf[a] = b;
    we[b] += we[a];
    return b;
}

int main () {
    scanf("%d", &k);

    for (int i = 0; i <= 3*k; i++) {
        uf[i] = i;
        we[i] = 1;
    }

    for (int i = 1; i <= 3*k; i++) {
    }
}
