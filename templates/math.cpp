#include <bits/stdc++.h>
#define MAX 2000000

using namespace std;

long fexp(long a, int r)
{
    long t;
    t = 1;
    while(r)
    {
        if( r%2 == 1 ) t *= a;
        a *= a;
        r /= 2;
    }
    return t;
}

long rfexp(long a, int r)
{
    long t;
    if( r == 0 ) return 1;
    if( r == 1 ) return a;
    t = fexp(a, r/2);
    return t*t*fexp(a, r%2);
}

long mdc(long a, long b)
{
    long t;
    while( b )
    {
        t = a;
        a = b;
        b = t%b;
    }
    return a;
}

long rmdc(long a, long b)
{
    return (a%b == 0) ? b : rmdc(b, a%b);
}

long mmc(long a, long b)
{
    return a*b/mdc(a,b);
}

long euclid(long a, long * x, long b, long * y)
{
    long d, ix, iy;
    if(a%b == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    d = euclid(b, &ix, a%b, &iy);
    *x = iy;
    *y = ix - iy*(a/b); 
    return d;
}

bitset<MAX> prime;
void sieve(int n)
{
    prime.set();
    prime[0] = prime[1] = 0;
    for( int i = 2; i <= n; i++ )
        if( prime[i] )
            for(int j = 2*i; j <= n ; j += i)
                prime[j] = 0;
}
