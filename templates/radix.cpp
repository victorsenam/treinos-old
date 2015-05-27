#include <bits/stdc++.h>
using namespace std;
typedef int num;

struct radixList
{
    long list, k;
    int r;
    
    void clear()
    {
        list = 0;
        k = 1;
    }

    bool empty()
    { return k == 1;}

    void push( int i )
    {
        // Poderia fazer uma lista
        // ligada, e nessa hora eu
        // apontaria para o próximo
        if( list + k*k < 0 )
            pop();
        list += i*k;
        k *= r;
    }

    int pop()
    {
        int ans = list%r;
        if( k == 1 ) return -1;
        list /= r;
        k /= r;
        return ans;
    }

} rL;

int main()
{
    ios::sync_with_stdio( false );
    int r, n, aux;
    cin >> r >> n;
    rL.clear();
    rL.r = r;
    while( n-- > 0 )
    {
        cin >> aux;
        cout << aux << " ";
        rL.push( aux );
    } cout << endl;

    while( !rL.empty() )
    {
        cout << rL.pop() << " ";
    }cout << endl;
}
