#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

void dianzhen(int num,int row){
    const char *nums[10][5] = {
        {"XXX", "X.X", "X.X", "X.X", "XXX"}, 
        {"..X", "..X", "..X", "..X", "..X"}, 
        {"XXX", "..X", "XXX", "X..", "XXX"}, 
        {"XXX", "..X", "XXX", "..X", "XXX"}, 
        {"X.X", "X.X", "XXX", "..X", "..X"}, 
        {"XXX", "X..", "XXX", "..X", "XXX"}, 
        {"XXX", "X..", "XXX", "X.X", "XXX"}, 
        {"XXX", "..X", "..X", "..X", "..X"}, 
        {"XXX", "X.X", "XXX", "X.X", "XXX"}, 
        {"XXX", "X.X", "XXX", "..X", "XXX"}  
    };
    printf("%s", nums[num][row]);
}

int main(){
    int n;
    scanf("%d",&n);
    int a[n];char temp[101];
    scanf("%s",temp);
    for(int i = 0; i < (int)strlen(temp); i++){
        a[i] = temp[i] - '0';
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < n; j++){
            dianzhen(a[j],i);
            if(j != n - 1){
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}