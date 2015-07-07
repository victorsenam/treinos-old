#include<bits/stdc++.h>

#define MV 101
#define N 10

using namespace std;
typedef int num;
int a[N], n;
set<int> s[MV*2+10];
set<int>::iterator it;


int ctOnes(int i) {
    int r = 0;
    while (i != 0) {
        r += i%2;
        i /= 2;
    }
    return r;
}

bool can (int v, int i) {
    for (it = s[v].begin(); it != s[v].end(); it++)
        if (*it & i == *it) 
            return 1;
    return 0;    
}

int main()
{
    int at;
    for (int i = 9; i >= 0; i--) {
        at = 1 << (i+1);
        s[i].insert(at);
        for (int j = i-1; j >= 0; j--) {
            at += 1 << (j+1);
            s[j+i].insert(at);
            s[j*10+i].insert(at);
            s[i*10+j].insert(at);
            for (int k = j-1; k >= 0; k--) {
                at += 1 << (k+1);
                s[10*i+j+k].insert(at);
                s[10*j+i+k].insert(at);
                s[10*k+i+j].insert(at);
                for (int l = k-1; l >= 0; l--) {
                    at += 1 << (l+1);
                    s[10*i+j+10*k+l].insert(at);
                    s[10*i+j+10*l+k].insert(at);
                    s[10*i+k+10*j+l].insert(at);
                    s[10*i+k+10*l+j].insert(at);
                    s[10*i+l+10*k+j].insert(at);
                    s[10*i+l+10*j+k].insert(at);

                    s[10*j+i+10*k+l].insert(at);
                    s[10*j+i+10*l+k].insert(at);
                    s[10*j+k+10*i+l].insert(at);
                    s[10*j+k+10*l+i].insert(at);
                    s[10*j+l+10*k+i].insert(at);
                    s[10*j+l+10*i+k].insert(at);

                    s[10*k+j+10*i+l].insert(at);
                    s[10*k+j+10*l+i].insert(at);
                    s[10*k+i+10*j+l].insert(at);
                    s[10*k+i+10*l+j].insert(at);
                    s[10*k+l+10*i+j].insert(at);
                    s[10*k+l+10*j+i].insert(at);

                    s[10*l+j+10*k+i].insert(at);
                    s[10*l+j+10*i+k].insert(at);
                    s[10*l+k+10*j+i].insert(at);
                    s[10*l+k+10*i+j].insert(at);
                    s[10*l+i+10*k+j].insert(at);
                    s[10*l+i+10*j+k].insert(at);
                    at -= 1 << (l+1);
                }
                at -= 1 << (k+1);
            }
            at -= 1 << (j+1);
        }
    }
    //printf("pre\n");
    
    int c = 1;
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", a+i);

        int res = (1 << 10) - 1;
        int resq = 10;
        for (int i = 0; i < (2<<10); i++) {
            int atq = ctOnes(i);
            if (atq > resq) continue;
            bool ok = 1;
            for (int j = 0; j < n && ok; j++) {
                if (!can(a[j], i))
                    ok = 0;
            }
            if (ok) {
                res = i;
                resq = atq;
            }
        }

        printf("Case %d:", c++);
        for (int i = 9; i >= 0; i--) {
            if ( ( (1 << i) & res ) == (1<<i) )
                printf(" %d", i);
        }
        printf("\n");
    }
}
