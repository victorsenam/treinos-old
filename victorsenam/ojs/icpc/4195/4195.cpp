#include <bits/stdc++.h>

using namespace std;

#define N 1002

int n, m;
unsigned int memo[N][N], memo2[N][N], s[N], aux;

unsigned int calc (int a, int b) {
    if (memo2[a][b] == ~0u) {
        memo2[a][b] = 0;
        for (int i = a; i < b; i++) {
            memo2[a][b] += (s[i]-s[i+1])*(s[i+1]-s[b+1]);
        }
         //   printf("[%d,%d] = %d\n", a, b, r);
    }
    return memo2[a][b];
}

unsigned int pd (int i, int k) {
    int r;
    if (i >= n) return 0;
    else if (memo[i][k] < ~0u);
    else if (k >= n-i-1) return 0;
    else if (!k) memo[i][k] = calc(i, n);
    else {
        for (int j = i; j <= n; j++) {
            r = calc(i, j) + pd(j+1, k-1);
            if (memo[i][k] > r) memo[i][k] = r;
        }
    }

    return memo[i][k];
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        s[n] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%u", &aux);
            aux += s[n-i];
            s[n-1-i] = aux;
            for (int j = 0; j <= m; j++) memo[i][j] = ~0u;
            for (int j = 0; j <= n; j++) memo2[i][j] = ~0u;
            memo2[n][i] = ~0u;
        }
        memo2[n][n] = ~0u;

        printf("%u\n", pd(0, m));
    }
}
