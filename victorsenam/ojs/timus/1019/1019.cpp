#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

const int MAX = 1000000001;

set<int> s[2];
set<int>::iterator bn[2][2], it[2];
int a, b, n, cc, ce;
char e;

int main () {
    scanf("%d", &n);

    s[0].insert(0);
    s[1].insert(MAX);

    while (n--) {
        scanf("%d %d %c", &a, &b, &e);

        cc = (e == 'w');
        
        for (int k = 0; k < 2; k++) {
            bn[k][0] = s[k].lower_bound();
            bn[k][1] = s[k].upper_bound();
        }

        if (s[0][1] == s[0].begin())
            ce = 1;
        else if (s[1][1] == s[1].begin())
            ce = 0;
        else {
            for (int k = 0; k < 2; k++) {
                it[k] = bn[k][0];
                it[k]--;
            }
            
            if (*it[0] < *it[1])
                ce = 1;
            else
                ce = 0;
        }

        for (int k = 0; k < 2; k++)
            for (it[k] = bn[k][0]; it[k] != bn[k][1]; it[k]++)
                s[k].erase(it[k]);

        it[cc] = s[cc].insert(a);
        it[ce] = s[ce].insert(b);
    }
}
