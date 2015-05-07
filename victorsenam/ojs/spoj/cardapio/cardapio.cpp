#include <bits/stdc++.h>

using namespace std;

#define N 4004

typedef int num;

map<string, int> mp;
map<string, int>::iterator it, jt;
stack<int> st;
int cnt;
bool val;
char temp[22];
vector<int> adj[N];
int t;
int n;
int a, b;
int o[N], ret[N];
set<int> seen;
bool isReq;

bool dfs (int v) {
    if (o[v] != -1) return 1;

    //printf("[%d]\n", v);
    o[v] = ret[v] = cnt++;
    st.push(v);

    for (int i = 0; i < adj[v].size(); i++) {
        if (o[adj[v][i]] != -1) {
            ret[v] = min(ret[v], o[adj[v][i]]);
        } else {
            if (!dfs(adj[v][i])) return 0;
            ret[v] = min(ret[v], ret[adj[v][i]]);
        }
    }

    if (ret[v] < o[v]) return 1;

    seen.clear();
    while (!st.empty()) {
        a = st.top();
       // printf("%d ", a);
        st.pop();
        if (seen.find((a+2*n)%(4*n)) != seen.end()) return 0;
        seen.insert(a);
    }
   // printf("\n");

    return 1;
}

int main () {
    t = 0;
    while (scanf("%d", &n) != EOF)  {
        for (int i = 0; i < 4*n; i++) {
            adj[i].clear();
            o[i] = -1;
        }
        while (!st.empty()) st.pop();

        mp.clear();
        for (int i = 0; i < n; i++) {
            scanf(" %s", temp);
            val = (temp[0] != '!');
            a = mp.insert(make_pair(temp+(!val), mp.size())).first->second + (!val)*2*n;

            scanf(" %s", temp);
            val = (temp[0] != '!');
            b = mp.insert(make_pair(temp+(!val), mp.size())).first->second + (!val)*2*n;
 //           printf("(+) %d -> %d\n", (a+2*n)%(4*n), b);
 //           printf("(+) %d -> %d\n", (b+2*n)%(4*n), a);

            adj[(a+2*n)%(4*n)].push_back(b);
            adj[(b+2*n)%(4*n)].push_back(a);
        }

/*
        for (it = mp.begin(); it != mp.end(); it++) {
            for (jt = mp.begin(); jt != mp.end(); jt++) {
                adj[it->second].push_back(jt->second + 2*n);
            }
        }
*/
        for (int i = 0; i < 4*n; i++) {
            printf("%d -> ", i);
            for (int j = 0; j < adj[i].size(); j++) {
                printf("%d ", adj[i][j]);
            }
            printf("\n");
        }

        printf("Instancia %d\n", ++t);
        printf("%d elementos\n", 2*n);
        bool isvalid = 1;
        for (int i = 0; i < 4*n && isvalid; i++) {
            if (adj[i].size()) isvalid = isvalid && dfs(i);
        }
        if (isvalid) printf("sim\n");
        else printf("nao\n");
        printf("\n");
    }
}
