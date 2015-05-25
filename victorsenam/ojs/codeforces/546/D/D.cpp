#include <bits/stdc++.h>
:w
:q

#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%d| ", __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) //
#endif

#define N 5000001

using namespace std;
typedef unsigned long long int num;

int crivo[N];
int a, b, m, p;
num cnt;

int fact(int i) {
    if (crivo[i]) return crivo[i];
    if (i < 2) return 0;
    
    for (int j = 2; j*j <= i; j++) {
        if (i%j) continue;
        crivo[i] = fact(j)+fact(i/j);
        return crivo[i];
    }
    
    return crivo[i] = 1;
}

int main () {
    for (int i = 0; i <= N; i++) crivo[i] = 0;

    for (int i = 2; i <= N; i++) {
        if (crivo[i]) continue;
        crivo[i] = 1;
        for (int j = 2; j*i <= N; j++)
            crivo[j*i] = fact(j) + 1;
    }
    
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &a, &b);
        
        cnt = 0;
        for (int i = b+1; i <= a; i++) {
            //debug("%d -> %d\n", i, fact(i));
            cnt += fact(i);
        }

        printf("%I64u\n", cnt);
    }
}
