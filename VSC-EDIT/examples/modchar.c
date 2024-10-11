#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int t,k,temp; char str[10000],ans[10000]; 
    scanf("%d",&t);
    while (t--){
        scanf("%s",str);
        scanf("%d",&k);
        int len = strlen(str);

        for(int i = 0; i < len; i++){
            temp = str[i] - '0';
            ans[i] = (temp % k) + '0';
        }
        ans[len] = '\0';
        printf("%s",ans);
    }

    return 0;
}