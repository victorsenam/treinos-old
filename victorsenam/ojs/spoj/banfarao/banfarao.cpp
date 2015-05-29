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

void setVal(int root, int lo, int hi, int ind);
void getInt(int res[3][2], int root, int lo, int hi, int ql, int qh);
void joinSol(int res[3][2], int left[3][2], int right[3][2]);

int main () {
    int res[3][2];

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        acc[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &acc[i]);
            acc[i] += acc[i-1];
            setVal(1, 0, n, i);
        }

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &a, &b);
            getInt(res, 1, 0, n, a-1, b);
        }
    }
}
