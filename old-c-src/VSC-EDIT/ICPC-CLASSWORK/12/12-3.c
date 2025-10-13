#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

double per_scoure(int m,int a[m]){
    int max = -1; int min = 11,sum = 0;
    for(int i = 0; i < m; i++){
        if(a[i] > max){
            max = a[i];
        }
        if(a[i] < min){
            min = a[i];
        }
        sum += a[i];
    }
    return ( sum - max - min ) / (m - 2.0);
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int a[m];

    if(n == 1){
        for(int i = 0; i < m; i++){
            scanf("%d",&a[i]);
        }
        printf("%.2lf",per_scoure(m,a));
        return 0;
    }
    
    double maxscoure = 0;
    while(n--){
        for(int i = 0; i < m; i++){
            scanf("%d",&a[i]);
        }
        if(per_scoure(m,a) > maxscoure){
            maxscoure = per_scoure(m,a);
        }
    }
    printf("%.2lf",maxscoure);
    return 0;
}