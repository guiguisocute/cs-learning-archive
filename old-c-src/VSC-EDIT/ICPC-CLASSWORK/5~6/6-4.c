#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int isperfect(int x){
    int sum = 1;
    for(int i = 2; i <= sqrt(x); i++){
        if(x % i ==0){
            sum += i;
            if(i != x / i){
                sum += x / i;
            }
        }
    }
    return sum == x;
}

int main(){
    int n;
    scanf("%d",&n);

    for(int i = 2;i <= n; i++){
        if(isperfect(i)){
            printf("%d\n",i);
        }
    }

    system("pause");
    return 0;
}