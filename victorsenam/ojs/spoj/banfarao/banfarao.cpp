#include <bits/stdc++.h>

using namespace std;
typedef int num;
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 200000

num seg[4*N][3][2];
int n, q, t, a, b;
int acc[N];

void joinSols(int to[3][2], int fl[3][2], int fr[3][2]) {
    int val = 0;
    
    // da esquerda
    to[0][0] = fl[0][0];
    if (acc[fr[0][1]] >= acc[fl[0][1]])
        to[0][1] = fr[0][1];
    else
        to[0][1] = fl[0][1];


    // da direita
    to[2][1] = fr[2][1];
    if (acc[fl[2][0]] <= acc[fr[2][0]])
        to[2][0] = fl[2][0];
    else
        to[2][0] = fr[2][0];


    // do centro
    int lini, lend, rini, rend;
    lini = fl[1][0];
    if (acc[fl[1][1]] > acc[fr[0][1]])
        lend = fl[1][1];
    else
        lend = fr[0][1];

    rend = fr[1][1];
    if (acc[fl[2][0]] <= acc[fr[1][0]])
        rini = fl[2][0];
    else
        rini = fr[1][0];

    if (acc[lend] - acc[lini] > acc[rend] - acc[rini]) {
        to[1][0] = lini;
        to[1][1] = lend;
    } else if (acc[lend] - acc[lini] < acc[rend] - acc[rini]) {
        to[1][0] = rini;
        to[1][1] = rend;
    } else if (lend - lini > rend - rini) {
        to[1][0] = lini;
        to[1][1] = lend;
    } else {
        to[1][0] = rini;
        to[1][1] = rend;
    }

    debug("fl [%d,%d) [%d,%d) [%d,%d)", fl[0][0], fl[0][1], fl[1][0], fl[1][1], fl[2][0], fl[2][1]);
    debug("fr [%d,%d) [%d,%d) [%d,%d)", fr[0][0], fr[0][1], fr[1][0], fr[1][1], fr[2][0], fr[2][1]);
    debug("to [%d,%d) [%d,%d) [%d,%d)", to[0][0], to[0][1], to[1][0], to[1][1], to[2][0], to[2][1]);
}

void setInit(int root, int ind, int lo, int hi) {
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
        
        debug("joining [%d,%d) from [%d,%d) and [%d,%d)", lo, hi, lo, mid, mid, hi);
        joinSols(seg[root], seg[root*2], seg[root*2+1]);
    }
}

void copyAns(int to[3][2], int from[3][2]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            to[i][j] = from[i][j];
}

bool getInt(int ans[3][2], int root, int ql, int qr, int lo, int hi) {
    if (lo >= ql && hi <= qr) {
        copyAns(ans, seg[root]);
        debug("ans[%d,%d) = seg[%d] = [%d,%d) [%d,%d) [%d,%d)", lo, hi, root, ans[0][0], ans[0][1], ans[1][0], ans[1][1], ans[2][0], ans[2][1]);
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

        if (!cl) {
            debug("[%d,%d) is [%d,%d)", lo, hi, mid, hi);
            copyAns(ans, ar);
        } else if (!cr) {
            debug("[%d,%d) is [%d,%d)", lo, hi, lo, mid);
            copyAns(ans, al);
        } else {
            debug("joining [%d,%d) from [%d,%d) and [%d,%d)", lo, hi, lo, mid, mid, hi);
            joinSols(ans, al, ar);
        }

        debug("ans[%d,%d) = [%d,%d) [%d,%d) [%d,%d)", lo, hi, ans[0][0], ans[0][1], ans[1][0], ans[1][1], ans[2][0], ans[2][1]);

        return 1;
    }
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        acc[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &acc[i]);
            acc[i] += acc[i-1];
        }
        
        scanf("%d", &q);

        for (int i = 0; i < n; i++)
            setInit(1, i, 0, n);

        int lala[3][2];
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);
            debug("Query [%d,%d)", a-1, b);
            getInt(lala, 1, a-1, b, 0, n);
            printf("%d %d\n", acc[lala[1][1]] - acc[lala[1][0]], lala[1][1] - lala[1][0]);
        }
    }
}
