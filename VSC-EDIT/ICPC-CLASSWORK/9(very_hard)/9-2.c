#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);

    int a[n][3];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            scanf("%d",&a[i][j]);
        }
    }

    int result = 0;
    for(int i = 0; i < n; i++){
        for(int j = i +1 ; j < n; j++){
                int sum1 = a[i][0] + a[i][1] + a[i][2];
                int sum2 = a[j][0] + a[j][1] + a[j][2];
                
                if (abs(a[i][0] - a[j][0]) <= 5 &&
                    abs(a[i][1] - a[j][1]) <= 5 &&
                    abs(a[i][2] - a[j][2]) <= 5){
                        if(abs(sum1 - sum2) <= 10){
                            result++;
                        }
                    }
            }
        }
    

    printf("%d",result);
    return 0;
}