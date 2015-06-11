#include<bits/stdc++.h>
using namespace std;
typedef int num;
num x, y, n, v[102], maxVal, ct;
bool mem[102][15000], solved[102][15000];

// Só chama para p <= n
bool findSubset( int p, num sum )
{
    if( solved[p][sum] ) return mem[p][sum];
    ct++;

    if( sum + x == maxVal/2 || sum + y == maxVal/2 )
        mem[p][sum] = true;
    else if( sum + x > maxVal/2 && sum + y > maxVal/2 )
        mem[p][sum] = false;
    else if ( p+1 <= n )
        mem[p][sum] = findSubset(p+1, sum) || findSubset(p+1, sum+v[p]);
    else
        mem[p][sum] = false;

    solved[p][sum] = true;
    return mem[p][sum];
}

int main()
{
    int tc = 1;
    while( scanf("%d %d %d", &x, &y, &n) > 0 && x && y && n )
    {
        printf("Teste %d\n", tc++);
        maxVal = x + y;
        for( int i = 0; i < n; i++ )
        {
            scanf("%d", v+i);
            maxVal += v[i];
        }

        for( int i = 0; i < (n+1)*maxVal; i++ )
            solved[i/maxVal][i%maxVal] = false;
        sort(v,v+n, greater<int>());
        ct = 0;

        if( maxVal%2 != 0 )
            printf("N\n");
        else if ( findSubset(0, 0) != 0 )
            printf("S\n");
        else
            printf("N\n");
        printf("[%d]\n", ct);
        printf("\n");
    }
}
