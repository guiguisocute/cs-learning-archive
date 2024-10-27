#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

struct student{
    char number[50];
    int a;
    int b;
    int c;
};

int main(){
    int n;
    scanf("%d",&n);

    struct student students[n];

    for(int i = 0; i < n; i++){
        scanf("%s %d %d %d",students[i].number, &students[i].a, &students[i].b, &students[i].c);
    }

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(abs(students[i].a - students[j].a) <= 5 && abs(students[i].b - students[j].b) <= 5 && abs(students[i].c - students[j].c) <= 5 && abs((students[i].a + students[i].b + students[i].c) - (students[j].a + students[j].b + students[j].c)) <= 10){
                printf("%s %s\n",students[i].number,students[j].number);
            }
        }
    }
    
    return 0;

}