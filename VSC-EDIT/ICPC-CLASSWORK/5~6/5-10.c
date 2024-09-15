#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, l, r, max_leftover = 0;
    scanf("%d %d %d", &n, &l, &r);


    for(int k = l; k <= r; k++){
        int leftover = k % n;
        if(leftover > max_leftover){
            max_leftover = leftover;  
        }
    }

    printf("%d", max_leftover);

    system("pause");
    return 0;
}