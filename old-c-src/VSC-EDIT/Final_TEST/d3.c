#include<stdio.h>
#define lli long long
lli jiecheng(int n){
    if(n == 0) return 1;
    return(n * jiecheng(n - 1));
}

int main(){
    double e = 1;
    int i = 1;
    int count = 0;
    while((1.0 / jiecheng(i)) >= 0.00001){
        e += (1.0 / jiecheng(i));
        i++;
        count++;
    }
    printf("%lf %d",e,count);
    return 0;
}