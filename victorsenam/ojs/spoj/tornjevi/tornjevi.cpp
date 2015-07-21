#include <bits/stdc++.h>

using namespace std;

#define first ff
#define second ss

const int N = 103;

int n, m;
vector<int> adj[4*N*N];
queue<pair<int, int> > q;
pair<int, int> aux, hor, ver;
int mat[N][N];
int ts;
int cnth, cntv;

int main () {
    scanf("%d %d", &n, &m);

    while (!q.empty()) q.pop();

    ts = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %s", c);

            if (c == 'T') {
                mat[i][j] = ts++;
                q.push(make_pair(i, j));
            } else if (c == 'n') {
                mat[i][j] = -1;
                q.push(make_pair(i, j));
            } else if (c == '#') {
                mat[i][j] = -2;
            } else {
                mat[i][j] = -3;
            }
        }
    }

    while (!q.empty()) {
        aux = q.front();
        q.pop();

        cntv = cnth = 0;
        for (int i = aux.ff+1; i < n && cntv; i++) {
            if (mat[i][aux.ss] == -2) break;
            if (mat[i][aux.ss] >= 0) {
                cntv = 1;
                ver.ff = i;
                ver.ss = aux.ss;
            }
        }
        for (int i = aux.ff-1; i >= 0 && cntv; i--) {
            if (mat[i][aux.ss] == -2) break;
            if (mat[i][aux.ss] >= 0) {
                cntv = -1;
                ver.ff = i;
                ver.ss = aux.ss;
        }

        for (int i = aux.ss+1; i < n && cntv; i++) {
            if (mat[aux.ff][i] == -2) break;
            if (mat[aux.ff][i] >= 0) {
                cnth = 1;
                ver.ff = aux.ff;
                ver.ss = i;
            }
        }
        for (int i = aux.ss-1; i >= 0 && cntv; i--) {
            if (mat[aux.ff][i] == -2) break;
            if (mat[aux.ff][i] >= 0) {
                cnth = -1;
                ver.ff = aux.ff;
                ver.ss = i;
            }
        }

        if (mat[aux.ff][aux.ss] == -1) {
            if (cntv && cnth) {
            }
        } else {
        }
    }
}
