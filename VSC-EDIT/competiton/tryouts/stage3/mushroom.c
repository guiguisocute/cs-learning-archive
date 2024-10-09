#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);
    int m[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&m[i]);
    }

    int q;
    scanf("%d",&q);
    int l[q],r[q];
    for(int i = 0; i < q; i++){
        scanf("%d %d",&l[i],&r[i]);
    }

    int sum[q];
    for(int i = 0; i < q; i++){
        sum[i] = 0;
        for(int j = l[i] - 1; j <= r[i] - 1; j++){
            sum[i] += m[j];
        }
    }

    for(int i = 0; i < q; i++){
        printf("%d\n",sum[i]);
    }

    system("pause");
    return 0;
}