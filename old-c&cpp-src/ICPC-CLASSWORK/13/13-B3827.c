#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

struct problem{
    int index;
    int scores[10];
    int sum;
};

int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    
    struct problem problems[n];

    for(int i = 0; i < n; i++){
        problems[i].index = i + 1;
        problems[i].sum = 0;
        for(int j = 0; j < k; j++){
            scanf("%d", &problems[i].scores[j]);
            problems[i].sum += problems[i].scores[j];
        }
    }

    int max1 = -1, max2 = -1;
    int index1 = -1, index2 = -1;    
    for(int i = 0; i < n; i++){
        if(problems[i].sum > max1){
            max2 = max1;
            index2 = index1;

            max1 = problems[i].sum;
            index1 = problems[i].index;
        }else if(problems[i].sum > max2){
            max2 = problems[i].sum;
            index2 = problems[i].index;
        }
    }

    printf("%d\n%d",index1,index2);

    return 0;
}