#include<stdio.h>
#include<stdlib.h>

int main(){
    int m,t,s;
    scanf("%d %d %d",&m,&t,&s);
    if(t != 0){
            int x = m - s / t - 1;
        if(s % t == 0){
            x += 1;
        }
        printf("%d",x >= 0? x : 0);  //三元运算符 (x >= 0 ? x : 0) 用于判断 x 是否为非负数：true执行第一个条件，false执行第二个条件
    }else{
        printf("0");
    }
    
    system("pause");
    return 0;

}