#include <bits/stdc++.h>
// Incompleto

#define N 100

vector<int> g[N];
queue<int> q;
int v[N], u[N];
int n, e, a, b;

int main () {
    scanf("%d %d", &n, &e);

    for (int i = 0; i < n; i++) v[i] = u[i] = 0;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &a, &b);
        
        g[--a].push_back(--b);
        g[b].push_back(a);
    }

    q.push(0);
    while (!q.empty()) {
        a = q.front();
        q.pop();

        if (!v[a]) {
            for (vector<int>::iterator it = g[a].begin(); it != g[a].end(); it++) {
                if (!v[*it]) q.push(*it);
            }
        }
        v[a]++;
    }

    printf("Possibilidades de Ciclos: ");
    for (int i = 0; i < n; i++) {
        if (v[i] > 1) printf("%d", i);
    }
    printf("Desconexões: ");
    for (int i = 0; i < n; i++) {
        if (!v[i]) printf("%d", i);
    }
    
    
}
