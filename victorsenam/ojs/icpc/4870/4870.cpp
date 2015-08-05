#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int K = 507;
const int F = 23;

int lim;
int n, k;
int f[N], d[N];
int memo[N*F][N];

int pd(int fun, int sec) {
    if (fun <= 0)
        return 0;
    if (sec >= n)
        return lim+1;

    if (memo[fun][sec] != -1)
        return memo[fun][sec];

    int ra = pd(fun, sec+1);
    if (ra <= lim)
        ra -= k;
    ra = max(0, ra);

    int rb = pd(fun-f[sec], sec+1);
    rb += d[sec];
    rb = min(lim+1, rb);
    
    memo[fun][sec] = min(ra, rb);
    return memo[fun][sec];
}

int main () {
    while (scanf("%d %d %d", &n, &k, &lim) != EOF && n && k && lim) {
        int hi = 0;
        int lo, mid;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", f+i, d+i);
            hi += f[i];
        }
        
        memset(memo, -1, sizeof memo);

        lo = 0;
        mid = (hi+lo+1)/2;
        while (lo < hi) {
            if (pd(mid, 0) <= lim)
                lo = mid;
            else
                hi = mid-1;
            mid = (hi+lo+1)/2;
        }

        printf("%d\n", mid);
    }
}
