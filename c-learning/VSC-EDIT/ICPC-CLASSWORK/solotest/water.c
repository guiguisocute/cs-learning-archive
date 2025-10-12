#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }
    int sum = 0,flag,j;
    for(int i = 1; i < n-1; i++){
        if(a[i+1]<a[i]){
            flag = 0;
            j = i + 1;
            while(a[j] < a[i]){
                if(j == n - 2 && a[j] == 0){
                    printf("%d",sum);
                    return 0;
                }
                flag += a[j];
                j++;
            }
            sum += ((a[i] * (j-i-1)) - flag);
            i = j;
        }
    }

    printf("%d",sum);
    return 0;
}