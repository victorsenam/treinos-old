#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000
#define MAX N*4+1

int n;

struct seg {
    int ie[MAX], id[MAX], sum[MAX], lazy[MAX];
    int v[N];

    void build(int root, int e, int d) {
        ie[root] = e;
        id[root] = d;
        
        sum[root] = v[e];

        if (e + 1 >= d) return;

        build(2*root, e, (e+d)/2);
        build(2*root+1, (e+d)/2, d);

        sum[root] = sum[2*root] + sum[2*root+1];
    }

    void refresh(int root, int e, int d) {
        sum[root] += lazy[root]*(id[root]-ie[root]);
        if (e + 1 < d) { 
            lazy[2*root] += lazy[root];
            lazy[2*root+1] += lazy[root];
        }
        lazy[root] = 0;
    }

    void update(int root, int e, int d, int v) {
        if (ie[root] >= d || id[root] <= e) return;
        if (ie[root] >= e && id[root] <= d) {
            lazy[root] += v;
            return;
        }

        update(root*2, (e+d)/2, d);
        update(root*2+1, e, (e+d)/2);
    }

    int getVal(int root, int e, int d) {
        
    }
};

int main () {
}
