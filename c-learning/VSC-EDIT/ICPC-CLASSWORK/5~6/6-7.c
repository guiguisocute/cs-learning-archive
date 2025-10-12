#include<stdio.h>
#include<stdlib.h>

int main(){
    int k,sub_1,sub_2,sub_3,found = 0;
    scanf("%d",&k);

    for(int i = 10000; i <= 30000; i++){
        sub_1 = i / 100;
        sub_2 = i % 10000 / 10;
        sub_3 = i % 1000;
        if(sub_1 % k == 0 && sub_2 % k == 0 && sub_3 % k == 0){
            printf("%d\n",i);
            found = 1;
        }
    }
    if(!found){
        printf("No\n");
    }

    system("pause");
    return 0;
}