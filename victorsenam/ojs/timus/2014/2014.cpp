#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

struct time {
    int month, day, hour, minute;
    bool operator < (const time & a) {
        if (month != a.month)
            return month < a.month;
        if (day != a.day)
            return day < a.day;
        if (hour != a.hour)
            return hour < a.hour;
        return minute < a.minute;
    }
};

struct seg {
    ll bal[N], deb[N];
    int esq[N], dir[N];

    void build (int r, int e, int d) {
        esq[r] = e;
        dir[r] = d;
        bal[r] = deb[r] = 0;

        if (e+1 >= d)
            return;
        build(2*r, e, (e+d)/2);
        build(2*r+1, (e+d)/2, d);
    }

    void update (int r, int p, ll val) {
        if (esq[r] > p || dir[r] <= p)
            return;
        if (req[r] == p && dir[r] == p+1) {
            if (val > 0)
                bal[r] = val;
            else
                deb[r] = val;
            return;
        }

        update(2*r, p, val);
        update(2*r+1, p, val);
    }
};

set<time> s;

int main () {
}
