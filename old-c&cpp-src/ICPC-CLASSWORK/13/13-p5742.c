#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

struct student{
    char number[50];
    int a;
    int b;
};

int main(){
    int n;
    scanf("%d",&n);

    struct student students[n];

    for(int i = 0; i < n; i++){
        scanf("%s %d %d",students[i].number, &students[i].a, &students[i].b);
    }
    for(int i = 0; i < n; i++){
        if(((students[i].a * 7 + students[i].b * 3) >= 800) && students[i].a + students[i].b > 140){
            printf("Excellent");
        }else{
            printf("Not excellent");
        }
        if(i != n - 1){
            printf("\n");
        }
    }

    return 0;
}