#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000
#define MAX 4*N+1

struct seg {
    int esq[MAX], dir[MAX];
    num sum[MAX], lazy[MAX];

    void build (int root, int e, int d) {
        esq[root] = e;
        dir[root] = d;
        sum[root] = 0;
        debug("Build : %d[%d,%d)", root, e, d);
        if (d - e == 1) return;
        build(2*root, e+(d-e)/2, d);
        build(2*root+1, e, e+(d-e)/2);
    }

    void refresh (int root) {
        sum[root] += (dir[root]-esq[root])*lazy[root];
        if (dir[root] - esq[root] > 1) {
            lazy[2*root] += lazy[root];
            lazy[2*root+1] += lazy[root];
        }
        lazy[root] = 0;
    }

    void add (int root, int e, int d, num x) {
        if (esq[root] >= e && dir[root] <= d) {
            lazy[root] += x;
            refresh(root);
            debug("Adding %d to [%d,%d) : gets %d[%d,%d)", x, e, d, root, esq[root], dir[root]);
            return;
        }
        refresh(root);
        if (esq[root] >= d || dir[root] <= e)
            return;

        refresh(root);
        add(2*root, e, d, x);
        add(2*root+1, e, d, x);
        sum[root] = sum[2*root] + sum[2*root+1];
    }

    num getVal (int root, int e, int d) {
        refresh(root);
        num res;
        if (esq[root] >= e && dir[root] <= d) res = sum[root];
        else if (esq[root] >= d || dir[root] <= e) res = 0;
        else res = (getVal(2*root, e, d) + getVal(2*root+1, e, d));

        debug("Getting [%d,%d) : %d[%d,%d) -> %d", e, d, root, esq[root], dir[root], res);
        return res;
    }
};

int n, a, b, k, v;
seg tree;

int main () {
    scanf("%d", &n);
    tree.build(1, 0, n);
    while (scanf("%d %d %d", &k, &a, &b) != EOF) {
        if (k == 1) {
            scanf("%d", &v);
            tree.add(1, a-1, b, v);
        } else {
            printf("%d\n", tree.getVal(1, a-1, b));
        }
    }
}
