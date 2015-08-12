#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;
const int P = 20;

num n, a;
int turn;
num memo[P][10][2];
int vis[P][10][2];

num solve (int pos, int dig, bool free) {
    if (pos == 0)
        return (free||((n%10)>=dig));

    if (vis[pos][dig][free] == turn)
        return memo[pos][dig][free];

    vis[pos][dig][free] = turn;
    num & m = memo[pos][dig][free];

    num mul = 1;
    for (int i = 0; i < pos; i++)
        mul *= 10;
    int val = (n/mul)%10;

    m = 0;
    if (free) {
        m = 10*solve(pos-1, dig, free) + mul;
    } else {
        m = solve(pos-1, dig, 0);
        if (val)
            m += val*solve(pos-1, dig, 1);
        if (val > dig)
            m += mul;
        else if (val == dig)
            m += n%mul+1;
    }

    return m;
}

num ss() {
    num res = 0;
    for (int i = 1; i < 10; i++)
        res += i*solve(18, i, 0);
    return res;
}

num countDig (num n) {
    num res = 0;
    while (n) {
        res += n%10;
        n /= 10;
    }
    return res;
}

int main () {
    scanf("%llu", &a);
    num lo = 0ull;
    num hi = 1000000000000000007ull;
    num ans = 0;

    while (lo < hi) {
        turn++;
        n = (hi+lo)/2;
        ans = ss();
        //printf("%llu: %llu\n", n, ans);
        if (ans >= a)
            hi = n;
        else
            lo = n+1;
    }
    hi = n;
    lo = 1ull;
    num rr;

    printf("%llu\n", ans);

    while (ans != a) {
        //printf("%llu [%llu,%llu]\n", ans, lo, hi);
        if (ans > a)
            ans -= countDig(lo++);
        else
            ans += countDig(++hi);
/*
        turn++;
        n = hi;
        rr = ss();

        turn++;
        n = lo-1;
        rr -= ss();
*/

 //       if (rr != ans)
 //           printf("FAIL %llu ~ %llu [%llu,%llu]\n", ans, rr, lo, hi);
    }

    printf("A%llu\n", ans);
    n = hi;
    turn++;
    ans = ss();

    n = lo-1;
    turn++;
    ans -= ss();
    printf("B%llu\n", ans);
    
    printf("%llu %llu\n", lo, hi);
}
