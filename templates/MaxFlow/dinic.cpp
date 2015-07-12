#include<bits/stdc++.h>
#define MV 5005
#define ME (2*30005)
using namespace std;
typedef unsigned long long ull;
typedef int num;
typedef int node;
typedef int edge;

// Vertices
int head[MV], curr[MV], dist[MV], Q[MV], vs;

// Arestas
int to[ME], next[ME], es;
num flow[ME], cap[ME];

// Entrada
int n, m;

void add(node u, node v, num cuv, num cvu)
{
    // Adiciona aresta de u->v com capacidade cuv
    to[es] = v; flow[es] = 0; cap[es] = cuv;
    next[es] = head[u]; head[u] = es++;

    // Adiciona aresta de v->u com capacidade cvu
    to[es] = u; flow[es] = 0; cap[es] = cvu;
    next[es] = head[v]; head[v] = es++;
}

// BFS no residual. Não tem muito o que explicar.
void bfs(node s)
{
    int qf=0, qb=0;
    for(int i=0;i<vs;i++) dist[i] = -1;
    dist[s] = 0;
    Q[qb++] = s;
    while( qf < qb )
    {
        node u = Q[qf++];
        for(edge e = head[u]; e >= 0; e = next[e])
            if( cap[e] > flow[e] && dist[to[e]] == -1 )
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++] = to[e];
            }
    }
}

num dfs(node s, node g, num af)
{
    num aux;
    if( s == g ) return af;
    for(edge &e = curr[s]; e >= 0 ; e = next[e] )
        if( dist[to[e]] == dist[s] + 1 &&
            cap[e] > flow[e]           &&
            ( aux=dfs( to[e], g, min(af,cap[e]-flow[e]) ) )>0 )
        {
            flow[e]   += aux;
            flow[e^1] -= aux;
            return aux;
        }
    return 0;
}

ull maxFlow(node src, node snk)
{
    ull ans=0;
    for( bfs(src); dist[snk] != -1; bfs(src) )
    {
        // Preciso limpar as arestas atuais
        for(int v=0; v < vs; v++ ) curr[v] = head[v];
        while( 42 )
        {
            num nf = dfs(src, snk,INT_MAX);
            if( nf > 0 ) ans += nf;
            else break;
        }
    }
    return ans;
}
