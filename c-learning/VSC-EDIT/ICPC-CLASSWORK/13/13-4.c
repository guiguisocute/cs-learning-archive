#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct student{
    char name[50];
    int age;
    int score;
};

struct student train(struct student s){
    s.age += 1;
    s.score = (int)(s.score * 1.2);
    if(s.score > 600){
        s.score = 600;
    }
    return s;
}

int main(){
    int n;
    scanf("%d",&n);

    struct student students[n];

    for(int i = 0; i < n; i++){
        scanf("%s %d %d",students[i].name, &students[i].age, &students[i].score);
    }
    for(int i = 0; i < n; i++){
        students[i] = train(students[i]);
        printf("%s %d %d",students[i].name,students[i].age,students[i].score);
        printf("\n");
    }

    return 0;
}