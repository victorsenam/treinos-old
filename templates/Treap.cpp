#include<bits/stdc++.h>
#define MT 16042 
using namespace std;

int lt[MT], rt[MT], pr[MT], val[MT], ts;
char key[MT];

void clearTreaps()
{
    ts = 0;
    srand( time(NULL) );
}

// Rotações 
int leftUp( int r )
{
    if( lt[r] < 0 ) return r;
    int c = lt[r];
    lt[r] = rt[c];
    rt[c] = r;
    return c;
}

int rightUp( int r )
{
    if( rt[r] < 0 ) return r;
    int c = rt[r];
    rt[r] = lt[c];
    lt[c] = r;
    return c;
}

int search( int r, int x )
{
    if( r < 0 || val[r] == x )
        return r;
    return (val[r] < x)? search(rt[r], x) : search( lt[r], x );
}

int removeNode( int r )
{
    int c;
    if( lt[r] > 0 && rt[r] > 0 )
    {
        if( pr[lt[r]] > pr[rt[r]] )
        {
            c = leftUp(r);
            rt[c] = removeNode( rt[c] );
            return c;
        }
        else
        {
            c = rightUp(r);
            lt[c] = removeNode( lt[c] );
            return c;
        }
    }
    else
    {
        c = rt[r] > 0 ? rt[r] : lt[r];
        return c;
    }
}

int remove( int r, int x )
{
    if( val[r] == x )
        return removeNode( r );

    int hit = r;
    while( hit > 0 && val[lt[hit]] != x && val[rt[hit]] != x )
        hit = val[hit] < x ? rt[hit] : lt[hit];

    if( hit < 0 ) return r;
    if( val[lt[hit]] == x )
        lt[hit] = removeNode( lt[hit] );
    else
        rt[hit] = removeNode( rt[hit] );
    return r;
}

int insert( int r, int x )
{
    if( r < 0 )
    {
        lt[ts]  = -1;
        rt[ts]  = -1;
        val[ts] =  x;
        pr[ts]  = random()%MT;
        return ts++;
    }
    else if( val[r] == x )
        return r;
    else
    {
        if( val[r] < x )
        {
            rt[r] = insert(rt[r], x);
            if( pr[rt[r]] > pr[r] )
                return rightUp(r);
            else
                return r;
        }
        else
        {
            lt[r] = insert(lt[r], x);
            if( pr[lt[r]] > pr[r] )
                return leftUp(r);
            else
                return r;
        }
    }
}

int max( int r )
{
    while( rt[r] > 0 )
        r = rt[r];
    return r;
}

int min( int r )
{
    while( lt[r] > 0 )
        r = lt[r];
    return r;
}
