#include<bits/stdc++.h>
#define MAX 102
typedef int num;
using namespace std;
char in[MAX], out[MAX];
num n, count, os;

int main()
{
    scanf("%d", &n);
    while( n-- > 0 )
    {
        scanf("%s ", in);
        os = 0;
        while( in[os] != 0 )
            out[os] = in[os++];
        if( os > 10 )
        {
            printf("%c%d%c\n", out[0], os-2, out[os-1]);
        }
        else
            printf("%s\n", in);
    }
}
