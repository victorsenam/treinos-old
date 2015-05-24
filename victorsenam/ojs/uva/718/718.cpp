#include <bits/stdc++.h>

using namespace std;
typedef int num;
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 100

int t, n, f, init, end;
pair<int, pair<int, int> > a;
vector<int> adj[N+2];
bool v[N+2];
int ele[N][2];

pair<int, pair<int, int> > euclid(int a, int b) {
    pair<int, pair<int, int> > aux;
    if (b == 0) aux = make_pair(a, make_pair(1, 0));
    else {
        int val, divi;
        aux = euclid(b, a%b);
    
        divi = a/b;
        /*
        if (a%b) {
            if (a < 0 && b > 0) divi--;
            else if (a > 0 && b < 0) divi--;
        }*/

        val = aux.second.first;
        aux.second.first = aux.second.second;
        aux.second.second = val - divi*aux.second.second;

    }
    
    debug("E (%d %d) -> %d %d %d", a, b, aux.first, aux.second.first, aux.second.second);

    return aux;
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
        scanf("%d %d %d %d", &f, &n, &init, &end);
        
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &ele[i][0], &ele[i][1]);   
            //debug("S %d %d", ele[i][0], ele[i][1]);
            adj[i].clear();
            v[i] = 0;
        }
        adj[n].clear();
        adj[n+1].clear();
        v[n] = v[n+1] = 0;
        
        for (int i = 0; i < n; i++) {
            if (init-ele[i][1] >= 0 && (init-ele[i][1])%ele[i][0] == 0) {
                adj[i].push_back(n);
                adj[n].push_back(i);
            }

            if (end-ele[i][1] >= 0 && (end-ele[i][1])%ele[i][0] == 0) {
                adj[i].push_back(n+1);
                adj[n+1].push_back(i);
            }

            for (int j = i+1; j < n; j++) {
                a = euclid(ele[i][0], -ele[j][0]);
                int b = ele[j][1] - ele[i][1];
                int c;

                debug("(%d)*(%d) - (%d)*(%d) = %d -> %d",
                    ele[i][0],
                    a.second.first,
                    ele[j][0],
                    a.second.second,
                    a.first,
                    b
                );

                if (b%a.first) continue;

                debug("(%d)*(%d) + (%d) = %d", a.second.first, ele[i][0], ele[i][1], a.second.first*ele[i][0] + ele[i][1]);
                b = a.second.first*ele[i][0] + ele[i][1];

                c = (((f-ele[i][1])/ele[i][0])-b)/ele[j][0];

                if (b + ele[j][0]*c < 0) continue;

                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }

        for (int i = 0; i < n+2; i++) {
            debug("%d", i);
            for (int j = 0; j < adj[i].size(); j++) {
                debug("\t%d", adj[i][j]);
            }
        }

        if (dfs(n))
            printf("It is possible to move the furniture.\n");
        else
            printf("The furniture cannot be moved.\n");
    }
}
