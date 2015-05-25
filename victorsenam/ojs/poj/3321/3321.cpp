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


#define N 10000

int n, m, a, b;
char c;
vector<int> adj[N];
int cnt[N];
bool app[N];
bool comm[N];
int par[N];
queue<int> q;

int setPar(int v) {
    if (cnt[v]) return 0;
    cnt[v] = 1;
    
    for (int i = 0; i < adj[v].size(); i++) {
        if (cnt[adj[v][i]]) continue;
        par[adj[v][i]] = v;
        cnt[v] += setPar(adj[v][i]);
    }

    return cnt[v];
}

void change(int v, int val) {
    debug("%d %d", v, val);
    if (v < 0) return;

    if (comm[v]) {
        val += !app[v] - app[v];
        app[v] = !app[v];
    }
        
    cnt[v] += val;
    comm[v] = 0;
    change(par[v], val);
}

int main () {
    scanf("%d", &n);

    par[0] = -1;
    for (int i = 0; i < n-1; i++) {
        cnt[i] = 0;
        app[i] = 1;
        comm[i] = 0;
        scanf("%d %d", &a, &b);
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    cnt[n-1] = 0;
    comm[n-1] = 0;
    app[n-1] = 1;

    setPar(0);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf(" %c %d", &c, &a);
        debug("%c %d", c, a);
        if (c == 'Q') {
            while (!q.empty()) {
                if (comm[q.front()])
                    change(q.front(), 0);
                q.pop();
            }
            printf("%d\n", cnt[a-1]);
        } else {
            q.push(a-1);
            comm[a-1] = !comm[a-1];
        }
    }
}
