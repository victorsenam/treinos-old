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

int f, e, ini, fim, t, mini, maxi;
vector<int> adj[N];
pair<int, int> ele[N];

inline int divfloor(int a, int b) {
    if (a < 0 && b < 0) return -divfloor(-a, -b);
    if (b < 0) return divfloor(-a, -b);

    if (a > 0 || a%b == 0) return a/b;
    return a/b-1;
}

int euclid (int a, int * k, int b, int * l) {
    int d;
    if (a < 0) {
        d = euclid(-a, k, b, l);
        *k = -*k;
        return d;
    }
    if (b < 0) {
        d = euclid(a, k, -b, l);
        *l = -*l;
        return d;
    }
    if (a%b == 0) {
        *k = 0;
        *l = 1;
        return b;
    }
    d = euclid(b, k, a%b, l);
    int aux = *k;
    *k = *l;
    *l = aux - *l*(a/b);
    return d;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &f, &e, &ini, &fim);
        for (int i = 0; i < e+2; i++) 
            adj[i].clear();

        for (int i = 0; i < e; i++)
            scanf("%d %d", &ele[i].first, &ele[i].second);

        for (int i = 0; i < e; i++) {
            if (ini - ele[i].second > 0 && (ini-ele[i].second)%ele[i].first == 0) {
                adj[i].push_back(e);
                adj[e].push_back(i);
            }
            if (fim - ele[i].second > 0 && (fim-ele[i].second)%ele[i].first == 0) {
                adj[i].push_back(e+1);
                adj[e+1].push_back(i);
            }
            for (int j = i + 1; j < e; j++) {
                int m, k, l, d;
                pair<int, int> x, y;
                x = ele[i];
                y = ele[j];
                d = y.second - x.second;
                m = euclid(x.first, &k, -y.first, &l);

                printf("---------\n");
                printf("(%d)*(%d) + (%d)*(%d) = %d\n", x.first, k, -y.first, l, m);
                if (d%m) continue;
                printf("try %d %d\n", i, j);
                 printf("(%d)*(%d) + (%d)*(%d) = %d\n", x.first, k*d/m, -y.first, l*d/m, d);

                k *= d/m;
                 printf("(%d)*h + (%d)\n", -x.first*y.first/m, x.first*k+x.second);

                mini = (x.first*k + x.second)%(-x.first*x.second/m);
                if (mini < 0) mini += abs(x.first*x.second/m);

                maxi = (x.first*y.first/m)*divfloor(f-1-mini, x.first*y.first/m) + mini;

                if (maxi < f && maxi >= max(x.second, y.second)) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                    
                    printf("%d %d connect on %d\n", i, j, maxi);
                }
            }
        }
    }
}
