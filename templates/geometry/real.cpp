#include<bits/stdc++.h>
using namespace std;
using cood  = double;
using point = complex<cood>;
const cood tau = 2*acos(-1.0);
const cood eps  = 1e-9;

// Operações básica
// Vetoriais e produtos
inline cood x(const point& a)
{ return real(a); }
inline cood y(const point& a)
{ return imag(a); }
inline cood inner(const point& a,const point& b)
{ return x(a)*x(b) + y(a)*y(b); }
inline cood cross(const point& a,const point& b)
{ return x(a)*y(b) - y(a)*x(b); }
inline cood area(const point& a,const point& b,const point& c)
{ return cross(b-a, c-a); }

// Utilidades ponto-retas:
// Projeta o ponto c na linha ab
inline point pLproj(point c,point a, point b)
{ return a + (b-a)*inner(c-a,b-a)/norm(b-a); }
// Projeta o ponto c no segmento ab
point pSproj(point c,point a,point b)
{
    if( abs(a-b) < eps ) return a;
    cood t = inner(c-a,b-a)/norm(b-a);
    if( t < 0 ) return a;
    if( t > 1 ) return b;
    return a + t*(b-a);
}
// Retorna distância entre ponto c e linha ab
inline cood pLdist(point c,point a,point b)
{ return cross(c-a,b-a)/abs(b-a); }
// Retorna distância entre ponto c e segmento ab
inline cood pSdist(point c,point a,point b) 
{ return abs(c - pSproj(c,a,b)); }

// Utilidade sobre retas:
// Retorna se ponto c entre a e b
inline bool between(point a,point b,point c)
{ return fabs(cross(a-c,b-c)) < eps && inner(a-c,b-c) < eps; }
// Testa se retas paralelas
inline bool parallelLines(point a,point b,point c,point d)
{ return fabs(cross(b-a,d-c)) < eps; }
// Retorna a intersecção entra ab e cd
// Amo álgebras de lie :D
point intersect(point a,point b,point c,point d)
{ return (a + (b-a)*(cross(c-a,d-c)/cross(b-a,d-c))); }

// Circulos
point circumcenter(point a,point b,point c)
{
    point ab = 0.5*(a+b) + (b-a)*polar(1.0,0.25*tau),
          bc = 0.5*(b+c) + (c-b)*polar(1.0,0.25*tau);
    return intersect(0.5*(a+b), ab, 0.5*(b+c), bc);
}
int cLintersect(point c, cood r, point a, point b, point& p0, point& p1)
{
    cood h = fabs(pLdist(c,a,b));
    if( h > r + eps || abs(b-a) < eps ) return 0; point p = pLproj(c,a,b);
    if( abs(p-c) < eps )
    {
        p0 = c + (r/abs(b-a))*(b-a);
        p1 = c - (r/abs(b-a))*(b-a);
    }
    else
    {
        point q = (sqrt(r*r-h*h)/abs(b-a))*(b-a);
        p0 = p + q; p1 = p - q;
    }
    if( abs(p0-p1) < eps ) return 1;
    return 2;
}
// Setar seed na main!
// srand( (unsigned) time(0) );
point spanningCircle( point * P, int ps, cood& r )
{
    if( ps < 2 )
    {
        r = 0.0; 
        return *P;
    }
    random_shuffle(P,P+ps);
    point ans = 0.5*(P[0]+P[1]); r = sqrt(norm(P[0]-ans));
    for( int i = 2; i < ps; i++ ) if( norm(ans-P[i]) > r*r )
    {
        ans = 0.5*(P[0]+P[i]); r = sqrt(norm(P[0]-ans));
        for( int j = 1; j < i; j++ )  if( norm(ans-P[j]) > r*r )
        {
            ans = 0.5*(P[i]+P[j]); r = sqrt(norm(P[i]-ans));
            for( int k = 0; k < j; k++ ) if( norm(ans-P[k]) > r*r )
            {
                ans = circumcenter(P[i],P[j],P[k]);
                r   = sqrt(norm(P[i]-ans));
            }
        }
    }
    return ans;
}
