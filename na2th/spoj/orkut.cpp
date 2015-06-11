#include<bits/stdc++.h>
#define MV 32
#define ME (32*16)
using namespace std;
typedef int num;
num head[MV], stat[MV], ans[MV], as, in[MV], is;
num to[ME], next[ME], es;
num n;
string rname[MV];

void dfs( int s )
{
    if( stat[s] == 1 ) return;
    stat[s] = 0;
    for( num e = head[s]; e >= 0; e = next[e] )
        if( stat[to[e]] == 0 ) return;
        else if ( stat[to[e]] == -1 )
            dfs( to[e] );
    ans[as++] = s;
    stat[s] = 1;
}

int main()
{
    ios::sync_with_stdio( false );
    int tc = 1;
    while( cin >> n && n  )
    {
        cout << "Teste " << tc++ << endl;
        // Grafo limpo
        memset( head, -1, sizeof head );
        es = 0;
        // Lê nomes
        map<string, int> names;
        string aux;
        for( int i = 0; i < n; i++ )
        {
            cin >> rname[i];
            names[rname[i]] = i;
        }
        // Limpa nós de entrada
        is = 0;
        for( int i = 0; i < n; i++ )
        {
            cin >> aux;
            num u = names[aux], d;
            cin >> d;
            if( d == 0 )
                in[is++] = u;
            for( int j = 0; j < d; j++ )
            {
                cin >> aux;
                num v = names[aux];
                to[es] = u; next[es] = head[v]; head[v] = es++;
            }
        }
        // Limpa resposta
        as = 0;
        memset( stat, -1, sizeof stat );
        while( is > 0 )
            dfs( in[--is] );
        if( as == n )
            while( as > 0 ) cout << rname[ans[--as]] << " ";
        else
            cout << "impossivel";
        cout << "\n" << endl;
    }
}
