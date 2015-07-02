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

int c[3];
int maxi;

int main () {
    scanf("%d %d %d", c, c+1, c+2);

    maxi = 0;
    for (int i = 0; i < 3; i++)
        maxi = max(max(maxi, min(c[i], (c[(i+1)%2]+c[(i+2)%2]))), c[i]);
    
    printf("%d\n", maxi);
}
