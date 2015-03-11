#include <bits/stdc++.h>

using namespace std;

#define N 50000
#define K 500

unsigned int d[N][K+1];
vector<unsigned int> g[N];
bool s[N];
int n, k, a, b, root, p;

long long int  contaPares (int v) {
    long long int r = 0;
    if (d[v][0]) return 0;
    d[v][0] = 1;
    s[v] = 1;
    
    for (vector<unsigned int>::iterator it = g[v].begin(); it != g[v].end(); it++) {
        if (d[*it][0]) continue;
        r += contaPares(*it);
    }

    for (vector<unsigned int>::iterator it = g[v].begin(); it != g[v].end(); it++) {
        if (s[*it]) continue;

        for (int j = 0; j < k && d[*it][j]; j++) d[v][j+1] += d[*it][j];

        for (int l = 0; l <= k-2; l++) {
            for (vector<unsigned int>::iterator jt = it + 1; jt != g[v].end(); jt++) {
                if (s[*jt]) continue;

                r += d[*it][l] * d[*jt][k-2-l];
            }
        }
    }

    s[v] = 0;
    r += d[v][k];

    return r;
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        s[i] = 0;
        for (int j = 0; j <= k; j++) d[i][j] = 0;
        
        if (i) {
            scanf("%d %d", &a, &b);
            a--;
            b--;

            g[a].push_back(b);
            g[b].push_back(a);
            if (i == 1) a = root;
        }
    }

/*
    for (int i = 0; i < n; i++) {
        printf("g[%d] : ", i+1);
        for (vector<unsigned int>::iterator jt = g[i].begin(); jt != g[i].end(); jt++) {
            printf("%d ", *jt+1);
        }
        printf("\n");
    }
*/

    printf("%I64d\n", contaPares(root));
}
