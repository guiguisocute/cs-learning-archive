#include<stdio.h>
#include<stdlib.h>

int main(){
    int s1,s2,s3;
    scanf("%d %d %d", &s1, &s2, &s3);

    int count[81] = {0};
    for(int i = 1; i <= s1; i++) {
        for(int j = 1; j <= s2; j++) {
            for(int k = 1; k <= s3; k++) {
                int sum = i + j + k;
                count[sum]++;
            }
        }
    }

    int max = 0, result = 0;
    for(int i = 3; i <= s1 + s2 + s3; i++){         
        if(count[i] > max){
            max = count[i];
            result = i;
        }
    }
    printf("%d",result);

    return 0;
}