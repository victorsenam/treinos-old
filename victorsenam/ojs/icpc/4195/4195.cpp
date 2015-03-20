#include <bits/stdc++.h>

using namespace std;

#define N 1000

int n, m;
unsigned int memo[N][N], s[N], aux;

unsigned int calc (int a, int b) {
    int r = 0;
    for (int i = a; i < b; i++) {
        r += (s[i]-s[i+1])*(s[i+1]-s[b+1]);
    }
    printf("[%d,%d] = %d\n", a, b, r);
    return r;
}

unsigned int pd (int i, int k) {
    int r, m;
    if (i >= n) return 0;
    if (memo[i][k] != ~0u);
    else if (!k) memo[i][k] = calc(i, n);
    else {
        m = ~0u;
        for (int j = i; j < n; j++) {
            r = calc(i, j) + pd(j+1, k-1);
            if (r < m) m = r;
        }
        memo[i][k] = m;
    }

    printf("(%d,%d) = %u\n", i, k, memo[i][k]);
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
        }

        printf("%u\n", pd(0, m));
    }
}
