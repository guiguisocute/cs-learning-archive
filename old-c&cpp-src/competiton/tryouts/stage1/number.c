#include<stdio.h>
#include<stdlib.h>

void dianzhen(int num,int row){
    const char *nums[10][5] = {
        {"XXX", "X X", "X X", "X X", "XXX"}, 
        {"  X", "  X", "  X", "  X", "  X"}, 
        {"XXX", "  X", "XXX", "X  ", "XXX"}, 
        {"XXX", "  X", "XXX", "  X", "XXX"}, 
        {"X X", "X X", "XXX", "  X", "  X"}, 
        {"XXX", "X  ", "XXX", "  X", "XXX"}, 
        {"XXX", "X  ", "XXX", "X X", "XXX"}, 
        {"XXX", "  X", "  X", "  X", "  X"}, 
        {"XXX", "X X", "XXX", "X X", "XXX"}, 
        {"XXX", "X X", "XXX", "  X", "XXX"}  
    };
    printf("%s", nums[num][row]);
}

int main(){
    int n;
    scanf("%d",&n);
    int in[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&in[i]);
    }

    for(int j = 0; j < 5; j++){
        for(int i = 0; i < n; i++){
            if(i > 0){
                printf("  ");
            }
            dianzhen(in[i],j);
        }
        printf("\n");
    }

    system("pause");
    return 0;
}