#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 10005;
const int ME = 100010;

int adj[MV], pend[MV], sol[MV], Q[MV];
int nxt[ME], to[ME], es;
num n,h, ss, qf, qb;
bool cyc, multSort;

int main()
{
    int tc;
    ios::sync_with_stdio(false);
    cin>>tc;
    while(tc--)
    {
        memset(adj, -1, sizeof adj);
        memset(pend, 0, sizeof pend);
        es = 0;
        cin >> n >> h;
        for(int i=0;i<h;i++)
        {
            node a,b;
            cin >> a >> b;
            a--;b--;
            pend[b]++;
            to[es] = b; nxt[es] = adj[a]; adj[a] = es++;
        }
        ss = 0; qf = 0; qb = 0;
        multSort = false;
        cyc      = false;
        while( ss < n )
        {
            for(node v=0;v<n;v++)
                if( pend[v] == 0 )
                    Q[qb++] = v;

            cyc = (qf == qb);
            multSort |= (qb-qf > 1);
            if( cyc ) break; 
            else 
            while( qf < qb )
            {
                sol[ss++] = Q[qf++];
                pend[sol[ss-1]]--;
                for(edge uv=adj[sol[ss-1]]; uv>=0 ; uv = nxt[uv])
                    pend[to[uv]]--;
            }
        }

        if( cyc )
            cout << "recheck hints\n";
        else if( multSort )
            cout << "missing hints\n";
        else
        {
            for(int i=0;i<n;i++)
            {
                if(i) cout << " ";
                cout << sol[i]+1;
            }
            cout << "\n";
        }
    }
}
