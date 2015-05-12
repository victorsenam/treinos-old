#include <bits/stdc++.h>

using namespace std;

#define N 500

struct node {
    int lin, col, dir;
    bool val;
};

vector<node> adj[N+1][N][4][2];
stack<node> st;
int ord[N+1][N][4][2];
int ret[N+1][N][4][2];
int com[N+1][N][4][2];
char mat[N][N];
node src, dst;
int qtb, qtw;
int n, m;
int cnt;
int cmps;
int t;
int mov[4] = {-1, 0, 1, 0};
int vizval;

node mknode(int lin, int col, int dir, bool val) {
    node nd;
    nd.lin = lin;
    nd.col = col;
    nd.dir = dir;
    nd.val = val;
    return nd;
}

bool eqNode(node a, node b) {
    if (a.lin != b.lin) return 0;
    if (a.col != b.col) return 0;
    if (a.dir != b.dir) return 0;
    if (a.val != b.val) return 0;
    return 1;
}

bool isEqual (int lin, int col, char val) {
    if (lin < 0 || lin >= n) return 0;
    if (col < 0 || col >= m) return 0;
    return mat[lin][col] == val;
}

bool checkStrong (node v) {
    printf("-----%d\n", cmps);
    while (!st.empty()) {
        src = st.top();
        printf("%d %d %d %d\n", src.lin, src.col, src.dir, src.val);
        st.pop();

        com[src.lin][src.col][src.dir][src.val] = cmps;
        if (com[src.lin][src.col][src.dir][!src.val] == cmps) return 0;

        if (eqNode(src, v)) break;
    }
    cmps++;

    return 1;
}

bool dfs (node v) {
    if (ord[v.lin][v.col][v.dir][v.val] != -1) return 1;

   // printf("%d %d %d %d\n", v.lin, v.col, v.dir, v.val);

    st.push(v);
    ord[v.lin][v.col][v.dir][v.val] = ret[v.lin][v.col][v.dir][v.val] = cnt++;

    for (int i = 0; i < adj[v.lin][v.col][v.dir][v.val].size(); i++) {
        dst = adj[v.lin][v.col][v.dir][v.val][i];
        if (ord[dst.lin][dst.col][dst.dir][dst.val] != -1) {
            if (com[dst.lin][dst.col][dst.dir][dst.val] != -1) {
                ret[v.lin][v.col][v.dir][v.val] = min(
                    ret[v.lin][v.col][v.dir][v.val],
                    ord[dst.lin][dst.col][dst.dir][dst.val]
                );
            }
        } else {
            if (!dfs(dst)) return 0;
            ret[v.lin][v.col][v.dir][v.val] = min(
                ret[v.lin][v.col][v.dir][v.val],
                ret[dst.lin][dst.col][dst.dir][dst.val]
            );
        }
    }

    if (ord[v.lin][v.col][v.dir][v.val] <= ret[v.lin][v.col][v.dir][v.val])
        return checkStrong(v);
    else return 1;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);

        while(!st.empty()) st.pop();
        cnt = cmps = 0;
        
        adj[N][N-1][0][0].clear();
        ord[N][N-1][0][0] = com[N][N-1][0][0] = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &mat[i][j]);
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 2; l++) {
                        adj[N][N-1][0][0].push_back(mknode(i, j, k, l));
                        adj[i][j][k][l].clear();
                        ord[i][j][k][l] = com[i][j][k][l] = -1;
                    }
                }
            }
        }

        qtb = qtw = 0;
        bool ok = 1;
        for (int i = 0; i < n && ok; i++) {
            for (int j = 0; j < m && ok; j++) {
                if (mat[i][j] == 'B') {
                    qtb++;
                    vizval = 0;
                    for (int k = 0; k < 4; k++) {
                        if (isEqual(i+mov[k], j+mov[(k+1)%4], 'W')) {
                            vizval++;
                            adj[i][j][k][0].push_back(mknode(i, j, (k+2)%4, 1));
                            adj[i][j][k][1].push_back(mknode(i, j, (k+2)%4, 0));
                            adj[i][j][k][0].push_back(mknode(i+mov[k], j+mov[(k+1)%4], (k+2)%4, 0));
                            adj[i][j][k][1].push_back(mknode(i+mov[k], j+mov[(k+1)%4], (k+2)%4, 1));
                        }
                    }
                    if (vizval < 2) ok = 0;
                } else if (mat[i][j] == 'W') {
                    qtw++;
                    vizval = 0;
                    for (int k = 0; k < 4; k++) {
                        if (isEqual(i+mov[k], j+mov[(k+1)%4], 'B')) {
                            vizval++;
                            for (int l = 0; l < 4; l++) {
                                if (l == k) continue;
                                adj[i][j][k][1].push_back(mknode(i, j, l, 0));
                            }
                            adj[i][j][k][1].push_back(mknode(i+mov[k], j+mov[(k+1)%4], (k+2)%4, 1));
                            adj[i][j][k][0].push_back(mknode(i+mov[k], j+mov[(k+1)%4], (k+2)%4, 0));
                        }
                    }
                    if (vizval < 1) ok = 0;
                }
            }
        }
        
 //       printf("== %d %d %d\n", ok, qtb, qtw);

        if (!ok || qtb*2 != qtw) printf("NO\n");
        else if (dfs(mknode(N, N-1, 0, 0))) printf("YES\n");
        else printf("NO\n");
    }
}
