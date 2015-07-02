#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100008

int n;
int a;
int cnt[N];
ll memo[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < N; i++)
        cnt[i] = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        cnt[a-1]++;
    }

    memo[0] = cnt[0];
    memo[1] = cnt[1]*2;

    for (int i = 2; i < N; i++)
        memo[i] = max(memo[i-2] + ((ll)cnt[i])*((ll)(i+1)), memo[i-1]);
    
    printf("%d\n", memo[N-1]);
}
