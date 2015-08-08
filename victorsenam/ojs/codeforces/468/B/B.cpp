#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define debug(...) {}
#endif

const int N = 100007;

int n, a, b;
int v[N], pos[N];
int sa, sb;
bool cor[N];
bool vis[N];
int deg[N];
int it;
int res;
vector<int> adj[N][2];

void dfs(int v, int c) {
    if (v == -1 || vis[v]) {
        if (v >= 0 && cor[v] == c)
            return;
        printf("NO\n");
        exit(0);
    }

    cor[v] = c;
    vis[v] = 1;
    res++;

    for (int j = 0; j < 2; j++)
        for (int i = 0; i < adj[v][j].size(); i++)
            dfs(adj[v][j][i], c);
}

int main () {
    scanf("%d %d %d", &n, &a, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d", pos+i);
        v[i] = pos[i];
    }

    sort(v, v+n);

    sa = -1;
    sb = -1;

    for (int i = 0; i < n; i++) {
        it = lower_bound(v, v+n, a-v[i]) - v;
        if (it == i) {
            sa = i;
            adj[i][0].push_back(i);
            deg[i]++;
        }
        if (it < n) {
            adj[i][0].push_back(it);
            deg[i]++;
        }

        it = lower_bound(v, v+n, b-v[i]) - v;
        if (it == i) {
            sb = i;
            adj[i][1].push_back(i);
            deg[i]++;
        }
        if (it < n) {
            adj[i][1].push_back(it);
            deg[i]++;
        }
    }

    res = 0;
    if (sa >= 0) dfs(sa, 0);
    if (sb >= 0) dfs(sb, 1);

    int ores = res;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0 || deg[i] == 1) {
            if (adj[i][1].size())
                dfs(i, 0);
            else
                dfs(i, 1);
        }

        if ((ores - res)%2) dfs(-1, 0);
    }

    for (int i = 0; i < n; i++)
        if (cor[i] == 0)
            dfs(i, 1);
    
    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%d ", cor[pos[i]]);
    printf("\n");
}
