#include<bits/stdc++.h>
using namespace std;
typedef int num;
num w;

bool solve( int w )
{
    bool good = false;
    for( int i = 2; !good && i < w; i += 2 )
        good = (w-i)%2 == 0;
    return good;
}

int main()
{
    scanf("%d", &w);
    if( solve(w) )
        printf("YES\n");
    else
        printf("NO\n");
}
