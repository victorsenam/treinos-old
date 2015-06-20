#include<cstdio>
#include<cstring>
#include<algorithm>
#define oo 1000000000
#define ME 101
typedef int num;
using namespace std;

num mem[ME][ME], res[ME][ME], exp[ME];
num n;

num solve( int l, int r )
{
    if( l > r || r >= n ) return oo;
    if( mem[l][r] == -1 )
    {
        if( l == r )
        {
            res[l][r] = exp[l];
            mem[l][r] = 0;
        }
        else
        {
            res[l][l] = exp[l];
            for( int k = l+1; k <= r; k++ )
                res[l][k] = (res[l][k-1] + exp[k])%100;

            mem[l][r] = oo;
            for( int k = l; k+1 <= r ; k++ )
                mem[l][r] = min( mem[l][r], solve(l,k) + solve(k+1,r) + res[l][k]*res[k+1][r] );
        }
    }
    return mem[l][r];
}

int main()
{
    while( scanf(" %d", &n ) > 0 )
    {
        for( int i = 0; i < n; i++ )
            scanf("%d", exp+i);

        memset( mem, -1 , sizeof mem );
        printf("%d\n", solve(0,n-1) );
    }
}
