#include <bits/stdc++.h>

using namespace std;

#define N 13
#define M 1594323
#define T 300

int n;
int a, c[2][N], equi[2], reg[2], maxTri[2], pot3[N+1];
int memo[M][T];
vector<int> trian;

int pd (int state, int i, int maxTri) {
    if (maxTri <= 0) return 0;
    if (memo[state][i] != -1) return memo[state][i];

    memo[state][i] = max(0, pd(state, i+1, maxTri));

    int k;
    for (k = 0; k < 13; k++)
        if ((trian[i]%pot3[k+1])/pot3[k] < (state%pot3[k+1])/pot3[k])
            break;

    if (k >= 13)
        memo[state][i] = max(memo[state][i], pd(state-trian[i], i+1, maxTri-1) + 1);

    return memo[state][i];
}

int main () {
    pot3[0] = 1;
    for (int i = 1; i < 14; i++) 
        pot3[i] = pot3[i-1]*3;

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            for (int k = j; k < N; k++) {
                if (i == j && j == k) continue;
                if (k >= j + i + 1) continue;

                trian.push_back(pot3[i] + pot3[j] + pot3[k]);
            }
        }
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < trian.size(); j++)
            memo[i][j] = -1;

    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < N; i++) c[0][i] = c[1][i] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            c[i%2][a-1]++;
        }
        equi[0] = equi[1] = reg[0] = reg[1] = 0;

        for (int i = 0; i < N; i++) {
            equi[0] += c[0][i]/3;
            equi[1] += c[1][i]/3;
            c[0][i] %= 3;
            c[1][i] %= 3;
        }

        printf("fp\n");
        if (equi[0] > equi[1]) printf("1\n");
        else if (equi[0] < equi[1]) printf("2\n");
        else {
            int a, b;

            maxTri[0] = maxTri[1] = 0;
            for (int i = 0; i < N; i++) {
                maxTri[0] += c[0][i];
                maxTri[1] += c[1][i];
                a += c[0][i]*pot3[i];
                b += c[1][i]*pot3[i];
            }

            reg[0] = pd(a, 0, maxTri[0]/3);
            reg[1] = pd(b, 0, maxTri[1]/3);

            if (reg[0] > reg[1]) printf("1\n");
            else if (reg[0] < reg[1]) printf("2\n");
            else printf("0\n");
        }
    }
}
