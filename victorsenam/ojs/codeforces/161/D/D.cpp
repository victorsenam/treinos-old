#include <bits/stdc++.h>

using namespace std;

#define N 50000
#define K 500

unsigned int d[N][K];
vector<unsigned int> g[N];
bool s[N];
int n, k, a, b, root;

long long int  contaPares (int v) {
    long long int r = 0;
    s[v] = 1;
    
    for (int i = 0; i < g[v].size(); i++) r += contaPares(g[v][i]);

    d[v][0] = 1;
    
    for (int i = 0; i < g[v].size(); i++) {
        if (s[g[v][i]]) continue;

        for (int j = 0; j < k; j++) d[v][j+1] += d[i][j];
        for (int j = i + 1; j < g[v].size(); j++) {
            if (s[g[v][j]]) continue;

            for (int l = 0; l <= k-2; l++) {
                r += d[g[v][i]][l] * d[g[v][j]][k-2-l];
            }
            printf("%d : (%d,%d) => r = %lld\n", v, i, j, r);
        }
    }

    r += d[v][k];

    printf("%d : r = %lld\n", v, r);
    return r;
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        s[i] = 0;
        for (int j = 0; j < k; j++) d[i][j] = 0;
        
        if (i) {
            scanf("%d %d", &a, &b);
            a--;
            b--;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("g[%d] : ", i);
        for (int j = 0; j < g[i].size(); j++) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }

    printf("%lld\n", contaPares(root));
}
