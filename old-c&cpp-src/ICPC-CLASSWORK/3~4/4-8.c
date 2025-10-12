#include<stdio.h>
#include<stdlib.h>

int main(){
    int x,y;
    scanf("%d %d",&x,&y);
    
    int big[7]={1,3,5,7,8,10,12};    //1 3 5 7 8 10 12
    int small[4]={4,6,9,11};  //4 6 9 11
    if(y == 2){
            if ((x % 4 == 0 && x % 100 != 0) || x % 400 == 0){   //闰年判定，1输出29，0输出28
                printf("29");
            }else{
                printf("28");
            }
                return 0;
            }
    for(int i = 0; i < 7;i++){
        if(y == big[i]){
           printf("31");
           return 0;
        }
    }
    for(int i = 0; i < 4;i++){
        if(y == small[i]);{
            printf("30");
            return 0;
        }
        

    }
    }