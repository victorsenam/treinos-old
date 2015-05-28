#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100000

num seg[4*N][3][2];
int n, q, t, a, b;
int acc[N];

void joinSols(int to, int fl, int fr) {
    int val = 0;
    
    // da esquerda
    seg[to][0][0] = seg[fl][0][0];
    seg[to][0][0] = seg[fl][0][1];
    if (acc[seg[fr][0][1]] > acc[seg[to][0][1]])
        seg[to][0][1] = seg[fr][0][1];

    // da direita
    seg[to][2][1] = seg[fr][2][1];
    seg[to][2][0] = seg[fr][2][0];
    if (acc[seg[fl][2][0]] < acc[seg[to][2][0]])
        seg[to][2][0] = seg[fl][2][0];

    // do centro
    int mend, mini;
    mend = seg[fl][1][1];
    if (acc[seg[fr][0][1]] > acc[mend])
        mend = seg[fr][0][1];
    mini = seg[fr][1][0];
    if (acc[seg[fl][2][0]] < mini)
        mini = seg[fl][2][0];

    if (acc[mend] - acc[seg[fl][1][0]] > acc[seg[fr][1][1]] - acc[mini])
        mini = seg[fl][1][0];
    else 
        mend = seg[fr][1][1];

    seg[to][1][0] = mini;
    seg[to][1][1] = mend;
}

void setInit(int root, int ind, int lo, int hi) {
    if (lo + 1 >= hi) {
        seg[root][0][0] = seg[root][1][0] = seg[root][2][0] = ind;
        seg[root][0][1] = seg[root][1][1] = seg[root][2][1] = ind+1;

        if (acc[ind+1]-acc[ind] < 0) {
            seg[root][0][1] = seg[root][1][1] = ind;
            seg[root][2][0] = ind+1;
        }
    }
    int mid = lo+(hi-lo)/2;
    if (ind < mid)
        setInit(2*root, ind, lo, mid);
    else
        setInit(2*root+1, ind, mid, hi);
    
    joinSols(root, root*2, root*2+1);
}

pair<int, int> getInt

int main () {
    while (t--) {
        scanf("%d", &n);
        scanf("%d", &acc[0]);
        for (int i = 1; i < n; i++) {
            scanf("%d", &acc[1]);
            acc[1] += acc[0];
        }
        
        for (int i = 0; i < n; i++) {
            setInit(1, i, 0, n);
        }
    }
}
