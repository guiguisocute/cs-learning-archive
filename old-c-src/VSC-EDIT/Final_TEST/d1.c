#include<stdio.h>

int main(){
    int score;
    scanf("%d",&score);
    score = score / 10;

    switch(score){
        case 10 : printf("ex"); break;
        case 9 : printf("ex"); break;
        case 8 : printf("good"); break;
        case 7 : printf("mid"); break;
        case 6 : printf("pass"); break;
        default : printf("sb"); break;
    }
    return 0;
}