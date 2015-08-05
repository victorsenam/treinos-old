#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100007

int n;
int v[N], s[N], memo[N];

int pd (int i) {
    int r = 0;
    int k;

    if (i >= n) return 0;
    if (memo[i]) return memo[i];

    k = s[v[i]] + 1;

    for (int j = i; v[j] == v[i]; j++) {
        r += v[i];

        if (v[j - i + s[v[i]] + 1] == v[i] + 1)
            k = j-i+s[v[i]]+1;

        memo[i] = max(memo[i], r + pd(k));
    }

    return memo[i];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        memo[i] = 0;
    }

    sort(v, v+n);

    for (int i = 0; i <= v[n-1]; i++)
        s[i] = 0;

    for (int i = 0; i < n; i++)
        s[v[i]] = max(s[v[i]], i);

    printf("%d\n", pd(0));
}
