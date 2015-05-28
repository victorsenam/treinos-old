#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000

num seg[4*N+1][3][2];
int n, q, t, a, b;
int acc[N];

void joinSols(int to[3][2], int fl[3][2], int fr[3][2]) {
    int val = 0;
    
    // da esquerda
    to[0][0] = fl[0][0];
    to[0][0] = fl[0][1];
    if (acc[fr[0][1]] > acc[to[0][1]])
        to[0][1] = fr[0][1];

    // da direita
    debug("to [%d,%d) [%d,%d) [%d,%d)", to[0][0], to[0][1], to[1][0], to[1][1], to[2][0], to[2][1]);
    debug("fl [%d,%d) [%d,%d) [%d,%d)", fl[0][0], fl[0][1], fl[1][0], fl[1][1], fl[2][0], fl[2][1]);
    debug("fr [%d,%d) [%d,%d) [%d,%d)", fr[0][0], fr[0][1], fr[1][0], fr[1][1], fr[2][0], fr[2][1]);
    to[2][1] = fr[2][1];
    to[2][0] = fr[2][0];
    if (acc[fl[2][0]] < acc[to[2][0]])
        to[2][0] = fl[2][0];

    // do centro
    int mend, mini;
    mend = fl[1][1];
    if (acc[fr[0][1]] > acc[mend])
        mend = fr[0][1];
    mini = fr[1][0];
    if (acc[fl[2][0]] < mini)
        mini = fl[2][0];

    if (acc[mend] - acc[fl[1][0]] > acc[fr[1][1]] - acc[mini])
        mini = fl[1][0];
    else 
        mend = fr[1][1];

    to[1][0] = mini;
    to[1][1] = mend;
}

void setInit(int root, int ind, int lo, int hi) {
    debug("%d %d %d %d", root, ind, lo, hi);
    if (lo + 1 >= hi) {
        seg[root][0][0] = seg[root][1][0] = seg[root][2][0] = ind;
        seg[root][0][1] = seg[root][1][1] = seg[root][2][1] = ind+1;

      //  if (acc[ind+1]-acc[ind] < 0) {
      //      seg[root][0][1] = seg[root][1][1] = ind;
      //      seg[root][2][0] = ind+1;
      //  }
    } else {
        int mid = lo+(hi-lo)/2;
        if (ind < mid)
            setInit(2*root, ind, lo, mid);
        else
            setInit(2*root+1, ind, mid, hi);
        
        joinSols(seg[root], seg[root*2], seg[root*2+1]);
    }
}

bool getInt(int ans[3][2], int root, int ql, int qr, int lo, int hi) {
    debug("[%d,%d) -> %d [%d,%d)", ql, qr, root, lo, hi);
    if (lo >= ql && hi <= qr) {
        ans = seg[root];
        debug("seg[root] [%d,%d) [%d,%d) [%d,%d)", seg[root][0][0], seg[root][0][1], seg[root][1][0], seg[root][1][1], seg[root][2][0], seg[root][2][1]);
        debug("ans [%d,%d) [%d,%d) [%d,%d)", ans[0][0], ans[0][1], ans[1][0], ans[1][1], ans[2][0], ans[2][1]);
        return 1;
    } else if (lo >= qr || hi <= ql) {
        debug("fail on %d", root);
        ans = NULL;
        return 0;
    } else {
        int al[3][2], ar[3][2];
        bool cl, cr;
        
        int mid = lo + (hi-lo)/2;
        cl = getInt(al, root*2, ql, qr, lo, mid);
        cr = getInt(ar, root*2+1, ql, qr, mid, hi);
        debug("got %d %d on %d", cl, cr, root);

        if (!cl)
            ans = ar;
        else if (!cr)
            ans = al;
        else 
            joinSols(ans, al, ar);

        return 1;
    }
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        scanf("%d", &acc[0]);
        for (int i = 1; i < n; i++) {
            scanf("%d", &acc[i]);
            acc[i] += acc[i-1];
        }
        
        scanf("%d", &q);

        for (int i = 0; i < n; i++)
            setInit(1, i, 0, n);

        int lala[3][2];
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);
            getInt(lala, 1, a-1, b, 0, n);
            printf("%d %d\n", acc[lala[1][1]] - acc[lala[1][0]], lala[1][1] - lala[1][0]);
        }
    }
}
