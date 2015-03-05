#include <bits/stdc++.h>

using namespace std;

#define QTD 100

vector<int> portas[QTD];
int mod[QTD], ener[QTD], seen[QTD];
int n, k, aux, newen, gg;

bool bfs(int i, int j) {
    if (i == j) return 1;
    seen[i] = 1;
    
    for (int k = 0; k < portas[i].size(); k++) {
        if (!seen[portas[i][k]] && bfs(portas[i][k], j)) return 1;
    }

    return 0;
}

int main () {
    while (scanf("%d", &n) != EOF && n != -1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &(mod[i]));
            scanf("%d", &k);
            ener[i] = 0;

            portas[i].clear();
            for (int j = 0 ; j < k; j++) {
                scanf("%d", &aux);
                portas[i].push_back(aux-1);
            }
        }

        ener[0] = 100;

        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n; j++) {
                if (ener[j] == 0) continue;
                for (int k = 0; k < portas[j].size(); k++) {
                    newen = ener[j] + mod[portas[j][k]];
                    if (newen > ener[portas[j][k]]) {
                        ener[portas[j][k]] = newen;
                    }
                }
            }
/*
            for (int j = 0; j < n; j++) {
                printf("%d ", ener[j]);
            }
            printf("<- %d\n", i);
*/            
            if (ener[n-1] > 0) break;
        }

        if (ener[n-1] > 0) gg = 1;
        else gg = 0;

        for (int j = 0; j < n && !gg; j++) {
            if (ener[j] == 0) continue;
            for (int k = 0; k < portas[j].size() && !gg; k++) {
                newen = ener[j] + mod[portas[j][k]];
                if (newen > ener[portas[j][k]]) { // ciclo ! :D
//                    printf("-> %d <- ", portas[j][k]);
                    for (int i = 0; i < n; i++) seen[i] = 0;
                    if (bfs(portas[j][k], n-1)) gg = 1;
//                    printf("%d\n", gg);
                }
            }
        }

        if (gg) printf("winnable\n");
        else printf("hopeless\n");
    }
}
