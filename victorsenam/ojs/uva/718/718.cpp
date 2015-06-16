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

#define N 102

int f, e, ini, fim;
vector<int> adj[N];
pair<int, int> ele[N];

int divfloor(int a, int b) {
    if (a < 0 && b < 0) return -divfloor(-a, -b);
    if (b < 0) return divfloor(-a, -b);

    if (a > 0 || a%b == 0) return a/b;
    return a/b-1;
}

int euclid (int a, int * k, int b, int * l) {
    
}

int main () {
    
}
