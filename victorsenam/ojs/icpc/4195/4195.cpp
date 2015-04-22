#include <bits/stdc++.h>

using namespace std;

#define N 1001

int n, k, v;
unsigned int m[N][N], s[N], aux;

int main () {
    while (scanf("%d %d", &n, &k) != EOF && n) {
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &aux);
            s[i] = s[i-1] + aux;
        }
        
        for (int j = 0; j <= k; j++) 
            m[0][j] = 0;
        for (int i = 1; i <= n; i++) 
            m[i][0] = m[i-1][0] + (s[i]-s[i-1])*s[i-1];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                v = m[i][j] = m[i][0];
                for (int b = 1; b < i; b++) {
                    v -= (s[b]-s[b-1])*(s[i]-s[b]);
                    m[i][j] = min(m[i][j], v+m[b][j-1]);
                }
 //               printf("%d %d -> %d\n", i, j, m[i][j]);
            }
        }

        printf("%d\n", m[n][k]);
    }
}
