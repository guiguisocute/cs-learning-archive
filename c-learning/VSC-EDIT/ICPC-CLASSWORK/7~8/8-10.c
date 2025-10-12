#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    int count = 0;
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i != j && i != k && j != k && a[i] + a[j] == a[k]){
                    count++;
                    goto NEXT;
                }
            }
        }
    NEXT:
        continue;
    }
    printf("%d",count);

    return 0;
}