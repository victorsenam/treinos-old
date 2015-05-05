#include <bits/stdc++.h>

using namespace std;

#define H 500

typedef long long int num;

int t;
int h, w;
num d;
num hei[H][H];
bool done[H][H];
num seen[H][H];
num turn, eqs, cnt;
int mov[4] = {1, -1, 0, 0};

bool dfs(int i, int j, num lo, num hi) {
    if (i < 0 || i >= h || j < 0 || j >= w) return 0;
    if (seen[i][j] == turn) return 0;
    if (hei[i][j] <= lo) return 0;
    if (hei[i][j] > hi) return 1;

    seen[i][j] = turn;

    if (hei[i][j] == hi) {
        done[i][j] = 1;
        eqs++;
    }

    bool r = 0;
    for (int k = 0; k < 4; k++)
        if(dfs(i+mov[k], j+mov[(k+2)%4], lo, hi)) r = 1;
    
    return r;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %lld", &h, &w, &d);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                scanf("%lld", &hei[i][j]);
                done[i][j] = 0;
                seen[i][j] = 0;
            }
        }

        turn = eqs = cnt = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (done[i][j]) continue;
                if (hei[i][j] < d) continue;
                turn++;
                eqs = 0;

                if(!dfs(i, j, hei[i][j] - d, hei[i][j])) cnt += eqs;
            }
        }

        printf("%d\n", cnt);
    }
}
