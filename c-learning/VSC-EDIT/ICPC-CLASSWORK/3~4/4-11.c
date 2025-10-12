#include<stdio.h>
#include<stdlib.h>

int main(){
    int R,B,C,D,E;
    scanf("%d %d %d %d %d",&R,&B,&C,&D,&E);    //C红正确，D蓝正确，E红放蓝or蓝放红
    
    if(C + D >= 2 * E){
        printf("%d",R * C + B * D);

        system("pause");
        return 0;
    }else{
        int min_RB = R < B ? R : B;
        printf("%d",min_RB * E * 2 + (R - min_RB)*C + (B - min_RB)*D );

        system("pause");
        return 0;
    }



}