#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

double dis(double x1,double x2,double y1,double y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1) * (y2 - y1)); 
}

int main(){
    double x1,y1,x2,y2,x3,y3;
    scanf("%lf %lf",&x1,&y1);
    scanf("%lf %lf",&x2,&y2);
    scanf("%lf %lf",&x3,&y3);

    printf("%.2lf",dis(x1,x2,y1,y2) + dis(x1,x3,y1,y3) + dis(x2,x3,y2,y3));

    return 0;
}