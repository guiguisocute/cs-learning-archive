#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    int rod[n + 1];
    for(int i = 0; i <= n; i++) {
    rod[i] = 0;
    }

    int a;
    for(int i = 0; i < m; i++){
        scanf("%d",&a);
        if(a - 2 >= 1){
            rod[a - 2]++;
        }
        if(a - 1 >= 1){
            rod[a - 1]++;
        }
        rod[a]++;
        if(a + 1 <= n){
            rod[a + 1]++;
        }
    }

    int count = 0;
    for(int i = 1; i <= n; i++){
        if(rod[i] >= 2){
            count++;
        }
    }

    printf("%d",count);
    
    return 0;
}