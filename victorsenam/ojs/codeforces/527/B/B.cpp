#include <bits/stdc++.h>

using namespace std;

#define N 200002

multimap<char, int> m;
vector<int> d;
int h, a, mini, ra, rb, n;
char sta[N], stb[N];

int main () {
    h = 0;
    
    scanf("%d", &n);
    scanf(" %s %s", sta, stb);

    for (int i = 0; i < n; i++) {
        if (sta[i] != stb[i]) {
            h++;
            d.push_back(i);
        }
    }

    mini = h;
    ra = rb = -1;

    for (vector<int>::iterator it = d.begin(); mini >= h-1 && it != d.end(); it++) {
        for (multimap<char, int>::iterator ps = m.lower_bound(stb[*it]); mini >= h-1 && ps != m.upper_bound(stb[*it]); ps++) {
            a = h-1;
            if (sta[ps->second] == stb[ps->second]) a++;
            if (sta[*it] == stb[ps->second]) a--;
            if (a < mini) {
                ra = *it;
                rb = ps->second;
                mini = a;
            }
        }
    }

    printf("%d\n", mini);
    if (ra == -1) printf("-1 -1\n");
    else printf("%d %d\n", ra+1, rb+1);

}
