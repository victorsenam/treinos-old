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

int f, e, ini, fim, t;
vector<int> adj[N];
pair<int, int> ele[N];

int divfloor(int a, int b) {
    if (a < 0 && b < 0) return -divfloor(-a, -b);
    if (b < 0) return divfloor(-a, -b);

    if (a > 0 || a%b == 0) return a/b;
    return a/b-1;
}

int euclid (int a, int * k, int b, int * l) {
    if (a < 0) {
        *k = -*k;
        return euclid(-a, k, b, l);
    }
    if (b < 0) {
        *l = -*l;
        return euclid(a, k, -b, l);
    }
    if (a%b == 0) {
        *k = 0;
        *l = 1;
        return b;
    }
    int d = euclid(b, k, a%b, l);
    int aux = *k;
    *k = *l;
    *l = aux - *l*(a/b);
    return d;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &f, &e, &ini, &fim);
        for (int i = 0; i < n+2, i++) 
            adj[i].clear();

        for (int i = 0; i < n; i++)
            scanf("%d %d", &ele[i].first, &ele[i].second);

        for (int i = 0; i < n; i++) {
            if (ini - ele[i].second > 0 && (ini-ele[i].second)%ele[i].first == 0) {
                adj[i].push_back(n);
                adj[n].push_back(i);
            }
            if (fim - ele[i].second > 0 && (fim-ele[i].second)%ele[i].first == 0) {
                adj[i].push_back(n+1);
                adj[n+1].push_back(i);
            }
            for (int j = i + 1; j < n; j++) {
                int m, k, l, d;
                pair<int, int> x, y;
                x = ele[i];
                y = ele[j];
                d = y.second - x.second;
                m = euclid(x.first, &k, -y.first, &l);

                if (d%m) continue;
                
            }
        }
    }
}
