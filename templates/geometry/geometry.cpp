#include<bits/stdc++.h>
#define MP  4005
#define eps 1e-9
typedef int cood;
typedef int point;
cood x[MP], y[MP];
point anchor;
using namespace std;

inline cood cross( point a, point b, point c )
{ return (x[b]-x[a])*(y[c]-y[b])-(y[b]-y[a])*(x[c]-x[b]); }
inline cood inner( point a, point b, point c = MP-1 )
{ return (x[a]-x[c])*(x[b]-x[c]) + (y[a]-y[c])*(y[b]-y[c]); }

bool lexLess( point a, point b )
{ return ( x[a]==x[b] ) ? y[a]<y[b]: x[a]<x[b] ; }

bool grahamLess( point a, point b )
{
    num val = cross(anchor, a, b);
    if( val == 0 ) return lexLess(a,b);
    return val > 0;
}

inline bool between( point a, point b, point c )
{ return ( cross(a,b,c) == 0 ) && ( inner(a,b,c) <= 0 ) ; }

inline double dist(double ax, double ay, point a)
{ return sqrt( (ax-x[a])*(ax-x[a]) + (ay-y[a])*(ay-y[a]) ); }

int findHull( point * P, int ps, point * H )
{
    if( ps < 3 )
    {
        for( int i = 0; i < ps; i++ ) H[i] = P[i];
        return ps;
    }
    int ans = 0;
    iter_swap( P, min_element(P, P+ps, lexLess) );
    anchor = P[0]; sort(P+1, P+ps, grahamLess);
    for( int i = 0; i < 3; i++ ) H[ans++] = P[i];
    for( int i = 3; i < ps; i++ )
    {
        while( ans > 1 && cross(H[ans-2], H[ans-1], P[i]) <= 0 ) ans--;
        H[ans++] = P[i];
    }
    return ans;
}

// Assume polígono ordenado em sentido anti-horário
bool inConvex( point * P, int ps, point q )
{
    int lo = 1,
        hi = ps-1;
    if( ps < 3 ) return between(P[0], P[1], q);
    while( lo + 1 < hi )
    {
        int mid = (lo+hi)/2,
            val = cross(P[0], P[mid], q);
        if( val == 0 ) return inner(P[0],P[mid],q) <= 0 ; 
        if( val > 0 )  lo = mid;
        else           hi = mid;
    }
    return ( cross(P[0] ,P[lo],q) >= 0 ) && 
           ( cross(P[lo],P[hi],q) >= 0 ) &&
           ( cross(P[hi],P[0] ,q) >= 0 ) ;
}
