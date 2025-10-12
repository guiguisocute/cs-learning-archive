#include<stdio.h>
#include<stdlib.h>

int main(){
    int t;
    scanf("%d",&t);

    long long int a[t],b[t],c[t],d[t];
    for(int i = 0; i < t; i++){
        scanf("%lld %lld %lld %lld",&a[i],&b[i],&c[i],&d[i]);
    }
    for(int i = 0; i < t; i++){
        if(a[i]*a[i] + b[i]*b[i] + c[i]*c[i] + d[i]*d[i] > a[i]*b[i] + b[i]* c[i] + c[i]*d[i] + d[i]*a[i]){
            printf("greater\n");
        }else if(a[i]*a[i] + b[i]*b[i] + c[i]*c[i] + d[i]*d[i] == a[i]*b[i] + b[i]* c[i] + c[i]*d[i] + d[i]*a[i]){
            printf("equal\n");
        }else{
            printf("less\n");
        }
    }

    system("pause");
    return 0;
}