#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,nmax,nmin;
    scanf("%d",&n);
    int a[n];

    for(int i = 0;i < n;i++){
        scanf("%d",&a[i]);
    }
    nmin = a[0];nmax = a[0];

    for(int i = 1;i < n; i++){
        if(a[i] < nmin){
            nmin = a[i];
        }
        if(a[i] > nmax){
            nmax = a[i];
        }
    }
    printf("%d",nmax - nmin);

    system("pause");
    return 0;
}