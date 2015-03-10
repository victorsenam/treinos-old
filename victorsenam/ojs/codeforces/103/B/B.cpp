#include <bits/stdc++.h>
// Incompleto

#define N 100

vector<int> g[N];
queue<int> q;
int v[N], cyc[N];
int n, e, a, b;

int main () {
    scanf("%d %d", &n, &e);

    for (int i = 0; i < n; i++) v[i] = cyc[i] = 0;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &a, &b);
        
        g[--a].push_back(--b);
        g[b].push_back(a);
    }

    q.push(0);
    while (!q.empty()) {
        a = q.front();
        q.pop();

        v[a] = 1;
        b = 0;
        for (vector<int>::iterator it = g[a].begin(); it != g[a].end(); it++) {
            if (v[*it]) c++;
            else q.push(*it);
        }
        if (b > 1) cyc[a] = 1;
    }
}
