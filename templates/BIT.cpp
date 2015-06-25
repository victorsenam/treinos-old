#include <bits/stdc++.h>
#define MV 1000
using namespace std;
typedef int num;

struct BIT 
{
    num freq[MV]; // Frequencias
    int n;        // Qtd. de "caixas"

    void set( int v )
    {
        n = v;
        memset( freq, 0, sizeof freq); // acho que fode se v = MV pq vc ta setando [0,MV)
    }

    // add numa posicao
    void insert( int i, num val )
    {
        for(; i <= n; i += (i&-i) )
            freq[i] += val;
    }

    // soma acumulada
    num count( int i )
    {
        num sum = 0;
        for( ; i > 0 ; i -= (i&-i) )
            sum += freq[i];
        return sum;
    }

    num sFreq( int i )
    {
        num ans = freq[i]; int goal;
        if( i > 0 )
            for( goal = i-(i&-i), i -= 1 ; i != goal; i -= (i&-i) )
                ans -= freq[i];
        return ans;
    }

} tree;

int main()
{
    tree.set( 100 );
    tree.insert(42 ,100);
    tree.insert(7 ,100);
    printf("%d\n", tree.count(42) );
    printf("%d\n", tree.count(7) );
    printf("%d\n", tree.sFreq(42));
}
