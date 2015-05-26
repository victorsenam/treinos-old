#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 500

int mat[N][N];
int a, b;
int n, m, q;
int maxis[N];
int maxg;
int mval;
int ma;

int main () {
    scanf("%d %d %d", &n, &m, &q);
    
    maxg = 0;
    for (int i = 0; i < n; i++) {
        maxis[i] = ma = 0;
        for (int j = 0; j < m; j++) {
            scanf("%d", &mat[i][j]);
            if (mat[i][j]) ma++;
            else {
                maxis[i] = max(maxis[i], ma);
                ma = 0;
            }
        }
        maxis[i] = max(maxis[i], ma);

        if (maxis[maxg] < maxis[i]) maxg = i;
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        a--;b--;
        
        mat[a][b] = (mat[a][b]+1)%2;
        mval = maxis[maxg];
        
        ma = 0;
        maxis[a] = 0;
        for (int j = 0; j < m; j++) {
            if (mat[a][j]) ma++;
            else {
                maxis[a] = max(maxis[a], ma);
                ma = 0;
            }
        }
        maxis[a] = max(maxis[a], ma);

        if (maxis[a] >= mval) maxg = a;
        else if (maxg == a) {
            for (int j = 0; j < m; j++)
                if (maxis[j] > maxis[maxg]) maxg = j;
        }

        printf("%d\n", maxis[maxg]);
    }
}
