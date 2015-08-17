#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000001;
const int N = 10007;

struct ran {
    int ini, fim, ind;
    bool cor;
};

bool operator < (const ran & a, const ran & b) {
    return a.ind > b.ind;
}

vector<evt> sim[N];
set<evt> valid;
map<int, int> times;
map<int, int>::iterator it;

inline ran ranm (int ini, int fim, int ind, bool cor) {
    ran t;
    t.ini = ini;
    t.fim = fim;
    t.ind = ind;
    t.cor = cor;
    return t;
}

int main () {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %c", &a, &b, &e);
        it = times.find(a);

        if (it == times.end()) {
            times[a] = times.size()-1;
            sim[times.size()-1].push_back(ranm(a, b, i, e=='w'));
        } else {
            sim[it->second].push_back(ranm(a, b, i, e=='w'));
        }
    }

    for (it = times.begin(); it != times.end(); it++) {
        for (int j = 0; j < sim[it->second].size(); j++)
            valid.insert(sim[it->second][j]);
        
        while (valid.size() && valid.begin()->fim <= it->second)
            valid.erase(valid.begin());
    }
}
