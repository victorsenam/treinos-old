#include <bits/stdc++.h>

using namespace std;

#define L 10002


char mul[4][4] = { {'h', 'i', 'j', 'k'}, {'i', 'h', 'k', 'j'}, {'j', 'k', 'h', 'i'}, {'k', 'j', 'i', 'h'} };
bool sig[4][4] = { {0, 0, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 1} };

inline char inc(char a, char b, bool *ini) {
    *ini = (sig[a-'h'][b-'h']+*ini)%2;
    return mul[a-'h'][b-'h'];
}
char remd(char a, char b, bool *ini) { // c*b = a
    int i;
    for (i = 0; i < 4; i++) {
        if (mul[i][b-'h'] == a) break;
    }
    *ini = (sig[i][b-'h']+*ini)%2;
    return i+'h';
}
char reme(char a, char b, bool *ini) { // b*c = a
    int i;
    for (i = 0; i < 4; i++) {
        if (mul[b-'h'][i] == a) break;
    }
    *ini = (sig[b-'h'][i]+*ini)%2;
    return i+'h';
}
void printState(int i, int j, char lo, bool ls, char mid, bool ms, char hi, bool hs) {
    printf("(%d,%d) -> ", i, j);
    if (ls) printf("-");
    printf("%c ", lo);
    if (ms) printf("-");
    printf("%c ", mid);
    if (hs) printf("-");
    printf("%c ", hi);
    printf("\n");
}

int main () {
    unsigned long long x, l, i, j;
    char s[L], lo, mid, hi, tot;
    bool ls, ms, hs, ts;
    int t;

    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%llu %llu", &l, &x);
        scanf(" %s", s);

        i = 0;
        j = l*x;
        lo = hi = mid = 'h';
        ls = hs = ms = 0;

        for (int k = 0; k < l; k++) {
            mid = inc(mid, s[k], &ms);
        }
        
        tot = mid;
        ts = ms;

        // exp log
        while (x > 1) {
            if (x % 2) {
                ms = (ms+ts)%2;
                mid = inc(mid, tot, &ms);
                x--;
            } else {
                ms = 0;
                mid = inc(mid, mid, &ms);
                x /= 2;
            }
        }

        printf("%c %d\n", mid, ms);
       // printState(i, j, lo, ls, mid, ms, hi, hs);
        while (i < j) {
            do {
                lo = inc(lo, s[i%l], &ls);
                mid = reme(mid, s[i%l], &ms);
                i++;
     //           printState(i, j, lo, ls, mid, ms, hi, hs);
            } while (i < j && (lo != 'i' || ls));
            if (i < j && hi == 'k' && !hs && mid == 'j' && !ms) break; 

            do {
                j--;
                hi = inc(s[j%l], hi, &hs);
                mid = remd(mid, s[j%l], &ms);
   //             printState(i, j, lo, ls, mid, ms, hi, hs);
            } while (i < j && (hi != 'k' || hs));
            if (i < j && mid == 'j' && !ms) break; 
        }
        printf("Case #%d: ", c);
        if (i < j) printf("YES");
        else printf("NO");
        printf("\n");
    }
}
