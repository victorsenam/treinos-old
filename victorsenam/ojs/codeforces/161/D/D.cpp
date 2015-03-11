#include <bits/stdc++.h>

using namespace std;

#define N 50000
#define K 500

unsigned int d[N][K+1];
vector<unsigned int> g[N];
bool s[N];
int n, k, a, b, root, p;

long long int contaPares (int v);
int main ();

long long int contaPares (int v) {
    long long int r = 0;
    
    if (s[v]) return 0;
    s[v] = 1;
    for (vector<unsigned int>::iterator it = g[v].begin(); it != g[v].end(); it++) {
        r += contaPares(*it);
    }
    s[v] = 0;

    for (vector<unsigned int>::iterator it = g[v].begin(); it != g[v].end(); it++) {
       if (s[v]) continue;

       
    }
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        s[i] = 0;
        for (int j = 0; j <= k; j++) d[i][j] = 0;

        if (i) {
            scanf("%d %d", &a, &b);

            g[--a].push_back(--b);
            g[b].push_back(a);
        }
    }

    for (root = 0; g[root].size() == 0; root++);

    printf("%I64d\n", contaPares(root));
}
