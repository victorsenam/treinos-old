#include <bits/stdc++.h>
#define MAX 1000

using namespace std;

typedef int cood;
typedef pair<cood, cood> point;

point P[MAX];
int hull[MAX], hs, ps;

cood cP(point a, point b, point c)
{
    // a.f a.s 1
    // b.f b.s 1
    // c.f c.s 1
    return ( 
            a.first*(b.second - c.second) +
            a.second*(c.first - b.first) +
            b.first*c.second - b.second*c.first
           );
}

bool properInter(point a, point b, point c, point d)
{
    return
        (
         ((cP(a, b, c) > 0)^(cP(a, b, d) > 0))
         &&
         ((cP(c, d, a) > 0)^(cP(c, d, b) > 0))
         );
}

bool grahamLess(point a, point b)
{
    cood val = cP( *P, a, b );
    if( !val )
        return (a.first) < (b.first);
    return val > 0;
}

void grahamScan()
{
    // Acha o ponto mais a esquerda
    int min = 0, i;
    for(i = 1; i < ps; i++)
        if( P[i] < P[min] )
            min = i;
    swap( P[0], P[min] );
    // Ordena pontos por angulo
    sort( P+1, P+ps, grahamLess);

    // Calcula o hull
    hs = 0;
    for( i = 0; i < 3; i++ )
        hull[hs++] = i;

    for( i = 3 ; i < ps; i++ )
    {
        while( hs > 1 && cP( P[hull[hs-2]], P[hull[hs-1]], P[i]) <= 0 )
            hs--;
        hull[hs++] = i;
    }
}
