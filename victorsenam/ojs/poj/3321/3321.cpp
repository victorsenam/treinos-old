#include <vector>
#include <queue>
#include <cstdio>

using namespace std;
typedef int num;
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 100000

int n, m, a, b;
char c;
vector<int> adj[N];
int cnt[N];
bool app[N];
bool comm[N];
int comms;
bool inQueue[N];
int par[N];

int buildTree (int v) {
    cnt[v] = 1;
    for (int i = 0; i < adj[v].size(); i++) {
        if (par[adj[v][i]] != -1) continue;
        par[adj[v][i]] = v;
        cnt[v] += buildTree(adj[v][i]);
    }
    return cnt[v];
}

void changeState (int v, int val) {
    if (v == -1) return;
    if (comm[v]) {
        val += !app[v] - app[v];
        app[v] = !app[v];
        comms--;
    }
    comm[v] = 0;
    cnt[v] += val;
    if (val != 0) 
        changeState(par[v], val);
}

void emmit (int v) {
    for (int i = 0; i < adj[v].size() && comms; i++)
        if (par[adj[v][i]] == v) emmit(adj[v][i]);

    changeState(v, 0);
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cnt[i] = comm[i] = inQueue[i] = 0;
        app[i] = 1;
        par[i] = -1;
        if (!i) continue;
        scanf("%d %d", &a, &b);
        if (b != 1) adj[a-1].push_back(b-1);
        if (a != 1) adj[b-1].push_back(a-1);
    }

    comms = 0;
    buildTree(0);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf(" %c %d", &c, &a);
        a--;

        if (c == 'Q') {
            emmit(a);
            printf("%d\n", cnt[a]);
        } else {
            comm[a] = !comm[a];
            comms += comm[a] - !comm[a];
        }
    }
}
