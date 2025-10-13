#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

double solve(int n,double x){
    if(n == 1){
        return sqrt(1 + x);
    }
    double temp;
    for(int i = 2; i <= n; i++){
        temp = sqrt( i + solve (n - 1,x));
    }
    return temp;
}

int main(){
    int n; double x;
    scanf("%lf %d",&x,&n);

    printf("%.2lf",solve(n,x));

    return 0;
}