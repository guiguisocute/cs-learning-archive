#include<stdio.h>
typedef struct Birthday{
    int year;
    int month;
    int day;
}Birh;

typedef struct Student{
    char name[100];
    Birh bith;
    float source[3]; 
}stu;

void swap_by_struct(stu* a, stu* b) {
    stu temp = *a;
    *a = *b;
    *b = temp;
}
void input_strcut(stu* students,int size){
    int i;
    for(i = 0; i < size; i++){
        scanf("%s",students[i].name);
        scanf("%d%d%d",&students[i].bith.year,&students[i].bith.month,&students[i].bith.day);
        scanf("%f%f%f",&students[i].source[0],&students[i].source[1],&students[i].source[2]);
    }
}
void printstrcut(stu* students,int size){
        int i;
        int* pa = students;
    for(i = 0; i < size; i++){
        printf("%s %d-%d-%d  %.2f %.2f %.2f\n",students[i].name,students[i].bith.year,students[i].bith.month,students[i].bith.day,students[i].source[0],students[i].source[1],students[i].source[2]);
        
    }
}

void bubble_stussouce_and_print(stu* students, int size){
    
}



int main(){
    stu students[3];
    input_strcut(students,3);
    printstrcut(students,3);

    return 0;
    
}