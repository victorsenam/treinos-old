#include<bits/stdc++.h>
#define MP 200
using namespace std;
typedef int num;
typedef int point;
typedef pair< pair<long long, int>, int > state;
num x[MP], y[MP];
point pend[MP], anchor, doc, por;
int ps, pds;
num t, m, c, d[MP];
vector< pair<int, long long> > adj[MP];
// Pontos guardados
// [0..c-1] cabines
// [c..c+2m] murais

inline int cP(point a, point b, point c)
{
    return x[a]*(y[b]-y[c]) +
           y[a]*(x[c]-x[b]) +
           x[b]*y[c] - x[c]*y[b];
}

inline num sign( num x )
{
    if( x > 0  ) return 1;
    if( x == 0 ) return 0;
    return -1;
}

inline long long dist(point a, point b)
{
    return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

inline bool improperInt( point a, point b, point c, point d )
{
    return ( sign(cP(a,b,c))*sign(cP(a,b,d)) <= 0 &&
             sign(cP(c,d,a))*sign(cP(c,d,b)) <= 0);
}

inline bool lexicalLess(point a,point b)
{
    if( x[a] == x[b] ) return y[a] < y[b];
    return x[a] < x[b];
}

inline bool grahamLess(point a,point b)
{
    num val = cP(anchor, a, b);
    if( !val ) return x[a] < x[b];
    return val > 0;
}

long long djs(int s, int e, int tic)
{
    state aux;
    for( int i = 0; i < ps; i++ )
        d[i] = INT_MAX;;
    d[s] = 0;
    priority_queue<state, vector<state>, greater<state> > pq;
    pq.push( make_pair( make_pair(0, tic) , s));
    while( !pq.empty() )
    {
        aux = pq.top(); pq.pop();
        long long lDist = aux.first.first;
        int tr = aux.first.second;
        int u  = aux.second;
        if( lDist <= d[u] )
            for( int i = 0; i < adj[u].size(); i++ )
            {
                int v = adj[u][i].first;
                if( adj[u][i].second == 0 && tr > 0 && lDist < d[v] )
                {
                    d[v] = lDist;
                    pq.push( make_pair( make_pair(lDist, tr-1), v));
                }
                else if( lDist + adj[u][i].second < d[v] )
                {
                    d[v] = lDist + adj[u][i].second;
                    pq.push( make_pair( make_pair( lDist + adj[u][i].second, tr), v) );
                }
            }
    }
}

int main()
{
    while( scanf("%d %d %d", &t, &m, &c) != EOF )
    {
        int x1,x2,y1,y2;
        // Primeiro endereço par >= c
        pds = 0;
        ps = c + c%2;
        for( int i = 0; i < m; i++ )
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x[ps] = x1; y[ps] = y1; pend[pds++] = ps++;
            x[ps] = x2; y[ps] = y2; pend[pds++] = ps++;
        }
        for( int i = 0; i < c; i++ )
        {
            scanf("%d %d", &x1, &y1);
            x[i] = x1; y[i] = y1; pend[pds++] = i;
        }
        scanf("%d %d", &x1, &y1);
        x[ps] = x1; y[ps] = y1; pend[pds++] = ps; doc = ps++;
        scanf("%d %d", &x1, &y1);
        x[ps] = x1; y[ps] = y1; pend[pds++] = ps; por = ps++;

        for( int i = 0; i < ps; i++ )
            adj[i].clear();
        
        // Monta o grafo das caminhadas em tempo
        while( pds > 0 )
        {
            // Acha ancora e remove da pendencia
            anchor = pend[0];
            int ai = 0, skipTo;
            for( int i = 1; i < pds; i++ )
                if( lexicalLess(pend[i], anchor) )
                {
                    anchor = pend[i];
                    ai     = i;
                }
            swap( pend[pds-1], pend[ai] ); pds--;
            sort( pend, pend+pds, grahamLess );
            for( int v = 0; v < pds; v++ )
            {
                long long d = dist( anchor, pend[v] );
                adj[anchor].push_back( make_pair(pend[v], d) );
                adj[pend[v]].push_back( make_pair(anchor, d) );

                // Se é mural 
                if( pend[v] > c && pend[v] < doc )
                {
                    skipTo = pend[v]^1;
                    adj[anchor].push_back( make_pair(skipTo, d) );
                    adj[skipTo].push_back( make_pair(anchor, d) );
                    while( grahamLess(pend[v], skipTo) ) v++;
                    if( pend[v] == skipTo ) v++;
                }
            }
        }

        for( int i = 0; i < c; i++ )
            for( int j = i+1; j < c; j++ )
            {
                bool free = true;
                for( int k = c+c%1; free && k < doc; k += 2 )
                    free = free && !improperInt(i,j,k,k+1);
                if( free )
                {
                    adj[i].push_back( make_pair(j, 0LL));
                    adj[j].push_back( make_pair(i, 0LL));
                }
            }

        djs(doc, por, t);
        printf("%.1f\n", sqrt(d[por]) );
    }
}
