#include <bits/stdc++.h>
#define MV 1000
using namespace std;
typedef int num;

struct Union
{
    int id[MV], // Links da árvore
        sz[MV], // Tamanho de cada subarvore
        n,      // número de vértices
        comp;   // Quantidade de componentes conexas

    void clear( int v )
    {
        n    = v;
        comp = n;
        for( int i = 0; i < n; i++ )
        {
            id[i] = i;
            sz[i] = 1;
        }
    }

    inline int find( int v )
    {
        id[v] = (id[v] == v) ? v : find( id[v] );
        return id[v];
    }

    inline bool connected(int u, int v)
    { return find(u) == find(v); }

    void union( int u, int v )
    {
        u = find(u); v = find(v);
        if( u == v ) return;
        if( sz[u] <= sz[v] )
        {
            id[u] = v;
            sz[v] += sz[u];
        }
        else
        {
            id[v] = u;
            sz[u] += sz[v];
        }
        comp--;
    }
} UF;
