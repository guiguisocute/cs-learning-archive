#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    float s,v;
    scanf("%f %f",&s,&v);
    float cost_min = ceil(s / v) + 10;
    float h = floor((480 - cost_min) / 60);
    float min = (480 - cost_min) - 60 * h;
    if(h >=0){
    printf("%02d:%02d\n",(int)h,(int)min);

    system("pause");
    return 0;
    }
    else{
        h += 24;
        printf("%02d:%02d\n",(int)h,(int)min);
            system("pause");
            return 0;
    }
}