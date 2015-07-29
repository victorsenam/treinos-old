#include <bits/stdc++.h>

using namespace std;

int n, m, x[10], siz;
int memo[10][10][2][2];
int visi[10][10][2][2];
int turn;
int res[10];

int pd (int dig, int pos, bool free, bool lz) {
    if (pos == -1) 
        return 0;

    int & m = memo[dig][pos][free][lz];
    if (visi[dig][pos][free][lz] == turn)
        return m;
    visi[dig][pos][free][lz] = turn;

    int mul = 1;
    for (int i = 0; i < pos; i++)
        mul *= 10;
    mul /= 10;

    if (free) {
        if (dig || lz)
            m = 10*pd(dig, pos-1, free, lz) + mul;
        else
            m = 9*pd(dig, pos-1, free, 1) + pd(dig, pos-1, free, 0);
    } else if (x[pos]) {
        if (dig || lz)
            m = x[pos]*pd(dig, pos-1, 1, lz) + pd(dig, pos-1, 0, lz) + mul;
        else
            m = (x[pos]-1)*pd(dig, pos-1, 1, 1) + pd(dig, pos-1, 0, 1) + pd(dig, pos-1, 0, 0);
    } else {
        m = pd(dig, pos-1, 0, lz);
        if (dig || lz)
            m += mul;
    }

    return m;
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        siz = 0;
        while (n > 0) {
            x[siz++] = n%10;
            n /= 10;
        }

        for (int i = 0; i < n; i++)
            res[i] = pd(i, siz, 0, 0);
        turn++;
        
        siz = 0;
        while (m > 0) {
            x[siz++] = m%10;
            m /= 10;
        }
        for (int i = 0; i < 10; i++)
            printf("%d ", pd(i, siz, 0, 0) - res[i]);
        turn++;
        printf("\n");
    }
}
