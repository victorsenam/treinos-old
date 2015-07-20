#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

vector<int> adj[N];
int ant[N][18];
int hei[N];
int que[N];
int n, m, k, t, a, b, ss;
int max1, max2, lc, mini;

void dfs(int v) {
    for (int i = 0; i < adj[v].size(); i++) {
        if (hei[adj[v][i]] == -1) 
            continue;
        int par = adj[v][i];
        for (int i = 0; i < 18; i++) {
            ant[v][i] = par;
            par = ant[par][i];
        }
    }

    for (int i = 0; i < adj[v].size(); i++) {
        if (hei[adj[v][i]] != -1)
            continue;
        hei[adj[v][i]] = hei[v]+1;
        dfs(adj[v][i]);
    }
}

int getLca(int v, int u) {
    if (v == u) return v;
    if (hei[v] > hei[u]) swap(u, v);

    if (hei[u] > hei[v]) {
        for (int i = 17; i >= 0; i--)
            if (hei[ant[u][i]] >= hei[v]) 
                return getLca(v, ant[u][i]);
    }

    for (int i = 17; i > 0; i++)
        if (ant[v][i] != ant[u][i])
            return getLca(ant[v][i], ant[u][i]);

    return getLca(ant[v][0], ant[u][0]);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            adj[i].clear();
            hei[i] = -1;
            for (int j = 0; j < 18; j++)
                ant[i][j] = 0;
        }

        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &a, &b);
            a--;
            b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        hei[0] = 0;
        dfs(0);

        scanf("%d", &m);
        while (m--) {
            scanf("%d", &k);

            max1 = max2 = mini = -1;
            for (int i = 0; i < k; i++) {
                scanf("%d", que+i);
                que[i]--;
                if (max1 == -1 || hei[que[i]] > hei[max1])
                    max1 = que[i];
                if (mini == -1 || hei[que[i]] < hei[mini])
                    mini = que[i];
            }

            if (k < 3) {
                printf("Yes\n");
                continue;
            }

            for (int i = 0; i < k; i++) {
                if (que[i] == max1)
                    continue;
                if (max2 == -1 || hei[que[i]] > hei[max2])
                    max2 = que[i];
            }

            lc = getLca(max1, max2);

 //           printf("max1 %d max2 %d mini %d lc %d\n", max1, max2, mini, lc);

            if (hei[mini] < hei[lc]) {
                printf("No\n");
                continue;
            }
            
            int ss;
            for (ss = 0; ss < k; ss++)
                if (getLca(que[ss], max1) != que[ss] && getLca(que[ss], max2) != que[ss])
                    break;

            if (ss == k)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
}
