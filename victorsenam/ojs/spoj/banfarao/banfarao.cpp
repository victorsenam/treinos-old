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

void joinSol(int res[3][2], int left[3][2], int right[3][2]) {
    int leftini, leftend;
    int rightini, rightend;

    res[0][0] = left[0][0];
    if (acc[left[0][1]] > acc[right[0][1]])
        res[0][1] = left[0][1];
    else
        res[0][1] = right[0][1];

    res[2][1] = right[2][1];
    if (acc[right[2][0]] < acc[left[2][0]])
        res[2][0] = right[2][0];
    else
        res[2][0] = left[2][0];

    leftini = left[1][0];
    if (acc[left[1][1]] > acc[right[0][1]])
        leftend = left[1][1];
    else
        leftend = right[0][1];

    rightend = right[1][1];
    if (acc[right[1][0]] < acc[left[2][0]])
        rightini = right[1][0];
    else
        rightini = left[2][0];

    if (acc[rightend] - acc[rightini] > acc[leftend] - acc[leftini]) {
        res[1][0] = rightini;
        res[1][1] = rightend;
    } else if (acc[rightend] - acc[rightini] < acc[leftend] - acc[leftini]) {
        res[1][0] = leftini;
        res[1][1] = leftend;
    } else if (rightend - rightini > leftend - leftini) {
        res[1][0] = rightini;
        res[1][1] = rightend;
    } else {
        res[1][0] = leftini;
        res[1][1] = leftend;
    }
}

void copyAns(int to[3][2], int from[3][2]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            to[i][j] = from[i][j];
}

bool getInt(int res[3][2], int root, int lo, int hi, int ql, int qh) {
    int mid, rleft[3][2], rright[3][2];
    if (lo >= ql && hi <= qh) {
        copyAns(res, seg[root]);
        return 1;
    }

    if (lo >= qh || hi <= ql)
        return 0;
    
    mid = lo+(hi-lo)/2;
    if (!getInt(rleft, 2*root, lo, mid, ql, qh))
        getInt(res, 2*root+1, mid, hi, ql, qh);
    else if (!getInt(rright, 2*root+1, mid, hi, ql, qh))
        copyAns(res, rleft);
    else
        joinSol(res, rleft, rright);

    return 1;
}

void setVal(int root, int lo, int hi) {
    int mid;
    if (lo + 1 >= hi) {
        seg[root][0][0] = seg[root][1][0] = seg[root][2][0] = lo;
        seg[root][0][1] = seg[root][1][1] = seg[root][2][1] = hi;
    } else {
        setVal(2*root, lo, lo+(hi-lo)/2);
        setVal(2*root+1, lo+(hi-lo)/2, hi);

        joinSol(seg[root], seg[2*root], seg[2*root+1]);
    }
}

int main () {
    int res[3][2];

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        acc[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &acc[i]);
            acc[i] += acc[i-1];
            setVal(1, 0, n);
        }

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);
            getInt(res, 1, 0, n, a-1, b);
            printf("%d %d\n", acc[res[1][1]] - acc[res[1][0]], res[1][1] - res[1][0]);
        }
    }
}
