#include <bits/stdc++.h>

using namespace std;

#define L 10002

struct quatern {
    char v;
    bool s;
};

char mul[4][4] = { {'h', 'i', 'j', 'k'}, {'i', 'h', 'k', 'j'}, {'j', 'k', 'h', 'i'}, {'k', 'j', 'i', 'h'} };
bool sig[4][4] = { {0, 0, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 1} };

inline quatern inc(quatern a, quatern b) {
    quatern c;
    c.v = mul[a.v-'h'][b.v-'h'];
    c.s = (a.s+b.s+sig[a.v-'h'][b.v-'h'])%2;
    return c;
}

quatern remd(quatern a, quatern b) { // c*b = a
    int i;
    quatern c;
    for (i = 0; i < 4; i++) {
        if (mul[i][b.v-'h'] == a.v) {
            c.v = i+'h';
            c.s = (a.s + b.s + sig[i][b.v-'h'])%2;
        }
    }
    return c;
}
quatern reme(quatern a, quatern b) { // b*c = a
    int i;
    quatern c;
    for (i = 0; i < 4; i++) {
        if (mul[b.v-'h'][i] == a.v) {
            c.v = i+'h';
            c.s = (a.s + b.s + sig[b.v-'h'][i])%2;
        }
    }
    return c;
}
void printState(int i, int j, quatern lo, quatern mid, quatern hi) {
    printf("(%d,%d) -> ", i, j);
    if (lo.s) printf("-");
    printf("%c ", lo.v);
    if (mid.s) printf("-");
    printf("%c ", mid.v);
    if (hi.s) printf("-");
    printf("%c ", hi.v);
    printf("\n");
}

int main () {
    unsigned long long x, l, i, j;
    quatern s[L], lo, mid, hi, tot;
    char temp;
    int t;

    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%llu %llu", &l, &x);

        i = 0;
        j = l*x;
        lo.v = mid.v = hi.v = 'h';
        lo.s = mid.s = hi.s = 0;

        for (int k = 0; k < l; k++) {
            scanf(" %c", &temp);
            s[k].v = temp;
            s[k].s = 0;
            mid = inc(mid, s[k]);
        }
        
        tot = mid;

        // exp log
        while (x > 1) {
            if (x % 2) {
                mid = inc(mid, tot);
                x--;
            } else {
                mid = inc(mid, mid);
                x /= 2;
            }
        }

        bool ok = 0;
        for (i = 0; i < x*l && !ok; i++) {
            lo = inc(lo, s[i%l]);
            tot = reme(tot, s[i%l]);
            if (lo.v != 'i' || lo.s) continue;

            mid = tot;
            hi = 'h';
            for (j = x*l-1; j >= i; j--) {
                hi = inc(s[j%l], hi);
                mid = remd(mid, s[j%l]);
                if (hi.v == 'k' && !hi.s && mid.v == 'j' && !mid.s) {
                    ok = 1;
                    break;
                }
            }
        }

 //       printState(i, j, lo, mid, hi);
        while (i < j) {
            do {
                lo = inc(lo, s[i%l]);
                mid = reme(mid, s[i%l]);
                i++;
   //             printState(i, j, lo, mid, hi);
            } while (i < j && (lo.v != 'i' || lo.s));
            if (i < j && hi.v == 'k' && !hi.s && mid.v == 'j' && !mid.s) break; 

            do {
                j--;
                hi = inc(s[j%l], hi);
                mid = remd(mid, s[j%l]);
     //               printState(i, j, lo, mid, hi);
            } while (i < j && (hi.v != 'k' || hi.s));
            if (i < j && mid.v == 'j' && !mid.s) break; 
        }
        printf("Case #%d: ", c);
        if (i < j) printf("YES");
        else printf("NO");
        printf("\n");
    }
}
