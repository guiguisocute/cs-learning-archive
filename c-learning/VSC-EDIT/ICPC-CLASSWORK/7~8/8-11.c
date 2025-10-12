#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    int sum = 0;
    for(int i = 0; i < m; i++) {
        sum += a[i];
    }

    int min = sum;
    for(int i = m; i < n; i++){
        sum = sum - a[i - m] + a[i];
        if(min > sum){
            min = sum;
        }
    }

    printf("%d",min);

    return 0;
}