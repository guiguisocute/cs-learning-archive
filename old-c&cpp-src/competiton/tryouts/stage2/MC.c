#include<stdio.h>
#include<stdlib.h>

int main(){
    int t;
    scanf("%d",&t);
    int n[t],m[t];
    for(int i = 0; i < t; i++){
        scanf("%d %d",&n[i],&m[i]);
    }

    int count[t];
    for(int i = 0; i < t; i++){
        count[i] = 0;
        while(n[i] >= 2 && m[i] >=1 ){
            n[i] -= 2;
            m[i] -= 1;
            count[i]++;
        }
        while(n[i] >= 1 && m[i] >= 2){
            n[i] -= 1;
            m[i] -= 2;
            count[i]++;
        }
        while(n[i] >= 2 && m[i] >= 2){
            n[i] -= 2;
            m[i] -= 2;
            count[i]++;
        }
        while(n[i] >= 2 && m[i] >= 3){
            n[i] -= 2;
            m[i] -= 3;
            count[i]++;
          }
          printf("%d\n",count[i]);
    }

    system("pause");
    return 0;
}