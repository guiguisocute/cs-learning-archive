#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define lli long long

int main(){
    int n;
    scanf("%d",&n);

    lli a[n + 1];
    for(int i = 1; i <=n; i++){
        scanf("%lld",&a[i]);        
    }

    lli m,p1,s1,s2;
    scanf("%lld %lld %lld %lld", &m, &p1, &s1, &s2);

    a[p1] += s1;

    lli sum1 = 0, sum2 = 0;
    for(int i = 1; i < m; i++){
        sum1 += (m - i) * a[i];
    }
    for(int i = m + 1; i <= n; i++){
        sum2 += (i - m) * a[i];
    }

    lli min = 1e15, where = 1;

    for(int i = 1; i <= n; i++){
        lli t1 =sum1, t2 = sum2;

        if(i < m){
            t1 += (m - i) * s2;
        }

        else if (i > m){
            t2 += (i - m) * s2;
        }

        lli d = llabs(t1 - t2);

        if (d < min) {
            min = d;
            where = i;
        }
    }
    printf("%lld", where);

    return 0;
    
}