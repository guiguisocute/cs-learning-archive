#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    int n,k;
    scanf("%d %d",&n,&k);

    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    a[k - 1] = ceil(a[k - 1] / 5.0);

    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }

    printf("%d",sum);

    return 0;
}