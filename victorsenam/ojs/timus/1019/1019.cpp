#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000001;

char e;
int n;
int a, b, c;
bool lc;
map<int, bool> mp;
map<int, bool>::iterator it, ls;
map<int, bool>::iterator lo, hi;

int main () {
    scanf("%d", &n);
    mp[-1] = 0;
    mp[0] = 1;
    mp[MAX] = 0;

    while (n--) {
        scanf("%d %d %c", &a, &b, &e);
        c = (e == 'w');
        it = mp.upper_bound(b);
        it--;

        mp[b] = it->second;
        mp[a] = c;

        lo = mp.find(a);
        lo++;
        hi = mp.find(b);
        while (lo != hi)
            mp.erase(lo++);
    }

    lc = 0;
    for (it = mp.begin(); it != mp.end(); it = ls) {
        ls = it;
        ls++;
        if (it->second == lc)
            mp.erase(it);
        else
            lc = !lc;
    }
    
    ls = mp.begin();
    int ma, mb;
    ma = mb = 0;
    for (it = mp.begin(); it != mp.end(); it++) {
        if (it == mp.begin())
            continue;

        if (ls->second == 1 && it->first - ls->first > mb - ma) {
            ma = ls->first;
            mb = it->first;
        }
        ls = it;
    }

    if (ls->second == 1 && MAX - ls->first > mb - ma) {
        ma = ls->first;
        mb = MAX;
    }

    printf("%d %d\n", ma, mb);
}
