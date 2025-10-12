#include<stdio.h>


typedef struct pair{
    int a;
    int b;
}pair;

typedef struct arr_and_size{
    int *arr;
    int size;
}Arrs;

int i;


void swap_by_str(pair* p){
    int temp = p->a;
    p->a = p->b;
    p->b = temp;
}

void swap_by_arr(int* a){
    int temp = a[0];
    a[0] = a[1];
    a[1] = temp;
}


void printstruct_classic(Arrs arr){
    for(i = 0; i < arr.size; i++){
        printf("%d\n",arr.arr[i]);
    }
    printf("\n");
}

void printstruct_point(Arrs* pa){
    for(i = 0; i < pa->size; i++){
        printf("%d\n",pa->arr[i]);
    }
    printf("\n");
}

void strcat_r(char* s1,char* s2){
    char* p1 = s1;
    char* p2 = s2;
    while(*p1){
        p1++;
    }
    while(*p2){
        *p1 = *p2;
        p1++;
        p2++;
    }
    *p1 = 0;
}

void strcpy_r(char* s1,char* s2){
    char* p1 = s1;
    char* p2 = s2;
    while(*p1){
        *p1 = *p2;
        p1++;
        p2++;
    }
    *p1 = 0;
}

int strlen_r(char* s1){
    char*p1 = s1;
    int sum = 0;
    while(*p1){
        sum++;
        p1++;
    }
    return sum;
}

int strcmp_r(char* s1,char* s2){
    char*p1 = s1;
    char*p2 = s2;
    while(*p1 || *p2){
        if(*p1 != *p2){
            return (*p1 - *p2);
        }
        p1++;
        p2++;
    }
    return 0;
}


int main(){
    //new solution for swap
    int a = 10,b = 20;
    pair p;
    p.a = a;    p.b = b;
    swap_by_str(&p);
    printf("%d %d\n",p.a,p.b);
    int arr[2] = {a,b};
    swap_by_arr(arr);
    printf("%d %d\n",arr[0],arr[1]);
    printf("=================================\n");

    //2 solution ptint the typical struct
    int arr_str[5] = {1,2,3,4,5};
    Arrs arrs;
    arrs.arr = arr_str;
    arrs.size = 5;
    printstruct_classic(arrs);
    printstruct_point(&arrs);
    printf("=================================\n");


    //build 4 string.h function by myself
    char s1[100] = "0123456789";
    char s2[100] = "abcdefghijklmn";
    char s3[100] = "!@#$&*()_+";
    strcat_r(s2,s1);
    strcpy_r(s3,s1);
    printf("%s\n%s\n%s\n%d\n%d\n",s1,s2,s3,strlen_r(s3),strcmp_r(s1,s3));
    printf("=================================\n");

    return 0;
}