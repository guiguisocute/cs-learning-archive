#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    int yuan,jiao;
    scanf("%d %d",&yuan,&jiao);
    printf("%d",(10 * yuan + jiao) / 19);

    system("pause");
    return 0;
}