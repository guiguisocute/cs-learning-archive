#include<stdio.h>
#include<stdlib.h>

int main(){
    int t;
    scanf("%d",&t);
    int n[t];
    for(int i = 0; i < t; i++){
        scanf("%d",&n[i]);
    }

    for(int i =0; i < t; i++){
        if (n[i] == 1) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

    }

    system("pause");
    return 0;

}

