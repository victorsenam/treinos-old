#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 101

int n, f, ini, fin;
int a[N];
int b[N];
int ar, br;
int k, l, x;
int m;
vector<int> adj[N+2];
bool v[N+2];
int t;

int euclid(int a, int b) {
    int m, aux;
    // altera k e l
    if (b == 0) {
        k = 1;
        l = 0;
        return a;
    }

    m = euclid(b, a%b);
    aux = k;
    k = l;
    l = aux - (a/b)*l;
    return m;
}

bool dfs(int u) {
    if (u == n+1) return 1;
    if (v[u]) return 0;

    v[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        if (dfs(adj[u][i])) return 1;

    return 0;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &f, &n, &ini, &fin);
        f--;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &a[i], &b[i]);
            adj[i].clear();
            v[i] = 0;
        }
        adj[n].clear();
        adj[n+1].clear();
        v[n] = v[n+1] = 0;

        for (int i = 0; i < n; i++) {
            if (ini >= b[i] && (ini-b[i])%a[i] == 0) {
                adj[i].push_back(n);
                adj[n].push_back(i);
                debug("START %d", i);
            }
            if (fin >= b[i] && (fin-b[i])%a[i] == 0) {
                adj[i].push_back(n+1);
                adj[n+1].push_back(i);
                debug("END %d", i);
            }

            if (b[i] > f) continue;
            for (int j = i+1; j < n; j++) {
                if (b[j] > f) continue;
                m = euclid(a[i], -a[j]);
                
                if ((b[j] - b[i])%m) {
                   // debug("(%d, %d) no meet", i, j);
                    continue;
                }

                k *= (b[j]-b[i])/m;

                ar = abs(a[i]*a[j]/m);
                br = (b[i] + a[i]*k)%ar;
                if (br > 0) br -= ar;

                //debug("%d <= %d*x+%d <= %d", max(b[i], b[j]), ar, br, f);
                //debug("%d <= x <= %d", (max(b[i], b[j])-br)/ar, (f-br)/ar);

                if ((max(b[i],b[j])-br)%ar && (f-br)%ar && (max(b[i],b[j])-br)/ar == (f-br)/ar) continue;
                //if (ar*((f-br)/ar)+br < (max(b[i], b[j]))) continue;
                debug("connected %d %d", i, j);

                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }


        if (dfs(n))
            printf("It is possible to move the furniture.\n");
        else
            printf("The furniture cannot be moved.\n");
    }
}
